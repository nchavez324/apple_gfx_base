#include "test_app/gfx/metal/renderer.hpp"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "test_app/gfx/apple/error.hpp"
#include "test_app/gfx/apple/math.hpp"
#include "test_app/gfx/camera.hpp"
#include "test_app/gfx/material.hpp"
#include "test_app/gfx/mesh_renderer.hpp"
#include "test_app/gfx/metal/material_buffer.hpp"
#include "test_app/gfx/metal/mesh_buffer.hpp"
#include "test_app/gfx/metal/shader.hpp"
#include "test_app/gfx/primitive.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace test_app::gfx {

Renderer::Renderer(std::filesystem::path resource_path)
    : mesh_observer_(),
      material_observer_(),
      resource_path_(std::move(resource_path)),
      command_queue_(nullptr),
      texture_(nullptr) {}

Renderer::Renderer(Renderer &&from)
    : mesh_observer_(),
      material_observer_(),
      resource_path_(std::move(from.resource_path_)),
      command_queue_(from.command_queue_),
      texture_(from.texture_) {
  from.mesh_observer_.disconnect();
  from.material_observer_.disconnect();
  from.command_queue_ = nullptr;
  from.texture_ = nullptr;
}

Renderer::~Renderer() {
  texture_->release();
  command_queue_->release();
  material_observer_.disconnect();
  mesh_observer_.disconnect();
}

std::optional<Error> Renderer::Prepare(Scene &scene, Surface &surface) {
  command_queue_ = surface.device()->newCommandQueue();

  if (auto err = LoadTexture(resource_path_, surface.device(), texture_)) {
    return err;
  }

  mesh_observer_.connect(scene.registry(), entt::collector.update<Mesh>());
  material_observer_.connect(scene.registry(),
                             entt::collector.update<Material>());

  return std::nullopt;
}

std::optional<Error> Renderer::Draw(Scene &scene, Surface &surface) {
  if (auto error = UploadMeshes(scene, surface)) return error.value();
  if (auto error = UploadMaterials(scene, surface)) return error.value();

  CA::MetalDrawable *current_drawable =
      surface.layer()->nextDrawable()->retain();
  // Skip rendering this frame, no problem.
  if (current_drawable == nullptr || command_queue_ == nullptr) {
    return {};
  }

  // Create a new command buffer for each render pass to the current drawable.
  MTL::CommandBuffer *command_buffer = command_queue_->commandBuffer();
  if (command_buffer == nullptr) {
    current_drawable->release();
    return Error(ErrorCode::UNAVAILABLE, "Command buffer was null");
  }

  surface.drawable_render_descriptor()
      ->colorAttachments()
      ->object(0)
      ->setTexture(current_drawable->texture());

  MTL::RenderCommandEncoder *render_encoder =
      command_buffer->renderCommandEncoder(
          surface.drawable_render_descriptor());
  if (render_encoder == nullptr) {
    current_drawable->release();
    return Error(ErrorCode::UNAVAILABLE, "Render command encoder was null");
  }

  render_encoder->setTriangleFillMode(MTL::TriangleFillModeFill);
  render_encoder->setFrontFacingWinding(MTL::WindingCounterClockwise);
  render_encoder->setCullMode(MTL::CullModeBack);
  render_encoder->setDepthStencilState(surface.depth_stencil_state());
  render_encoder->setFragmentTexture(
      texture_, static_cast<NS::UInteger>(TextureArgument::COLOR));

  glm::uvec2 viewport_size = surface.viewport_size();
  entt::entity camera_entity = entt::null;
  auto camera_view = scene.registry().view<Camera, Transform>();
  for (auto [entity, c, t] : camera_view.each()) {
    camera_entity = entity;
    break;
  }
  auto camera = scene.registry().get<Camera>(camera_entity);
  auto camera_transform = scene.registry().get<Transform>(camera_entity);
  glm::mat4 view = glm::inverse(camera_transform.transform());
  glm::mat4 projection = camera.projection_matrix(viewport_size);

  auto drawable_view = scene.registry().view<MeshRenderer, Transform>();
  for (auto [entity, mesh_renderer, transform] : drawable_view.each()) {
    entt::entity mesh_entity = mesh_renderer.mesh();
    entt::entity material_entity = mesh_renderer.material();
    if (mesh_entity == entt::null ||
        !scene.registry().all_of<MeshBuffer>(mesh_entity) ||
        material_entity == entt::null ||
        !scene.registry().all_of<MaterialBuffer>(material_entity)) {
      continue;
    }
    MeshBuffer &mesh_buffer = scene.registry().get<MeshBuffer>(mesh_entity);
    MaterialBuffer &material_buffer =
        scene.registry().get<MaterialBuffer>(material_entity);

    render_encoder->setRenderPipelineState(
        material_buffer.render_pipeline_state());

    glm::mat4 model = transform.transform();
    glm::mat4 model_view_projection = projection * view * model;
    simd::float4x4 model_view_projection_simd =
        apple::math::matrix::from_glm(model_view_projection);
    Uniforms uniforms = {
        /* model_view_projection= */ model_view_projection_simd,
    };

    render_encoder->setVertexBytes(
        &uniforms, /* length= */ sizeof(uniforms),
        /* index= */
        static_cast<NS::UInteger>(VertexFunctionArgument::UNIFORMS));
    render_encoder->setVertexBuffer(
        mesh_buffer.vertex_buffer(), /* offset= */ 0,
        /* index= */
        static_cast<NS::UInteger>(VertexFunctionArgument::VERTICES));
    render_encoder->drawIndexedPrimitives(
        mesh_buffer.primitive_type(), mesh_buffer.index_count(),
        mesh_buffer.index_type(), mesh_buffer.index_buffer(),
        /* buffer_offset= */ 0);
  }

  render_encoder->endEncoding();
  // Schedule a present once the framebuffer is complete
  command_buffer->presentDrawable(current_drawable);
  // Finalize rendering here & push the command buffer to the GPU
  command_buffer->commit();

  current_drawable->release();
  return std::nullopt;
}

std::optional<Error> Renderer::Stop(Scene &scene) {
  auto delete_mesh_view = scene.registry().view<MeshBuffer>();
  for (auto [entity, buffer] : delete_mesh_view.each()) {
    scene.registry().erase<MeshBuffer>(entity);
  }

  auto delete_material_view = scene.registry().view<MaterialBuffer>();
  for (auto [entity, buffer] : delete_material_view.each()) {
    scene.registry().erase<MaterialBuffer>(entity);
  }

  return std::nullopt;
}

std::optional<Error> Renderer::UploadMeshes(Scene &scene, Surface &surface) {
  // TODO: For one obviously, we don't need to upload the buffers every frame if
  // they haven't changed.
  // TODO: Two, we don't need to allocate separate buffers for each mesh. We can
  // layout one big buffer (as long as the data types are the same?) and then
  // refer to everything by offsets.

  // Delete buffers for deleted meshes.
  auto delete_view = scene.registry().view<MeshBuffer>(entt::exclude<Mesh>);
  for (auto [entity, buffer] : delete_view.each()) {
    scene.registry().erase<MeshBuffer>(entity);
  }

  // Upload buffers for new meshes.
  auto create_view = scene.registry().view<Mesh>(entt::exclude<MeshBuffer>);
  for (auto [entity, mesh] : create_view.each()) {
    auto buffer = MeshBuffer::Build(surface.device(), mesh);
    if (!buffer.ok()) return std::move(buffer.error());
    scene.registry().emplace<MeshBuffer>(entity, std::move(*buffer));
    continue;
  }

  // Modify buffer contents for updated buffers.
  for (const auto entity : mesh_observer_) {
    auto new_buffer =
        MeshBuffer::Build(surface.device(), scene.registry().get<Mesh>(entity));
    if (!new_buffer.ok()) return std::move(new_buffer.error());
    // TODO: Actually write to buffer instead of just making a new one..
    scene.registry().replace<MeshBuffer>(entity, std::move(*new_buffer));
  }
  mesh_observer_.clear();

  return std::nullopt;
}

std::optional<Error> Renderer::UploadMaterials(Scene &scene, Surface &surface) {
  // Delete buffers for deleted materials.
  auto delete_view =
      scene.registry().view<MaterialBuffer>(entt::exclude<Material>);
  for (auto [entity, buffer] : delete_view.each()) {
    scene.registry().erase<MaterialBuffer>(entity);
  }

  // Upload buffers for new materials.
  auto create_view =
      scene.registry().view<Material>(entt::exclude<MaterialBuffer>);
  for (auto [entity, material] : create_view.each()) {
    entt::entity shader_entity = material.shader();
    if (!scene.registry().all_of<Shader>(shader_entity)) {
      std::cout << "DOOM: material did not have a shader" << std::endl;
      continue;
    }
    Shader &shader = scene.registry().get<Shader>(shader_entity);
    auto buffer =
        MaterialBuffer::Build(surface.device(), surface.pixel_format_draw(),
                              surface.pixel_format_depth(), material, shader);
    if (!buffer.ok()) return std::move(buffer.error());
    scene.registry().emplace<MaterialBuffer>(entity, std::move(*buffer));
    continue;
  }

  // Modify buffer contents for updated buffers.
  for (const auto entity : material_observer_) {
    Material &material = scene.registry().get<Material>(entity);
    entt::entity shader_entity = material.shader();
    if (!scene.registry().all_of<Shader>(shader_entity)) {
      std::cout << "DOOM: material did not have a shader" << std::endl;
      continue;
    }
    Shader &shader = scene.registry().get<Shader>(shader_entity);
    auto new_buffer =
        MaterialBuffer::Build(surface.device(), surface.pixel_format_draw(),
                              surface.pixel_format_depth(), material, shader);
    if (!new_buffer.ok()) return std::move(new_buffer.error());
    // TODO: Actually write to buffer instead of just making a new one..
    scene.registry().replace<MaterialBuffer>(entity, std::move(*new_buffer));
  }
  material_observer_.clear();

  return std::nullopt;
}

std::optional<Error> Renderer::LoadTexture(
    const std::filesystem::path &resource_path, MTL::Device *device,
    MTL::Texture *&texture) {
  std::filesystem::path texture_path = resource_path / "texture.jpg";

  int iwidth, iheight, channels;
  stbi_uc *pixels =
      stbi_load(texture_path.c_str(), &iwidth, &iheight, &channels,
                /* desired_channels= */ STBI_rgb_alpha);
  if (!pixels) {
    return Error(ErrorCode::INVALID_ARGUMENT,
                 "Failed to load texture image: " + texture_path.string());
  }
  NS::UInteger width = static_cast<NS::UInteger>(iwidth);
  NS::UInteger height = static_cast<NS::UInteger>(iheight);

  auto texture_descriptor =
      MTL::TextureDescriptor::alloc()->init()->autorelease();
  texture_descriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm_sRGB);
  texture_descriptor->setWidth(width);
  texture_descriptor->setHeight(height);

  texture = device->newTexture(texture_descriptor);
  if (texture == nullptr) {
    stbi_image_free(pixels);
    return Error(ErrorCode::UNAVAILABLE, "Could not create texture");
  }
  NS::UInteger bytes_per_row = 4 * width;
  MTL::Region region(0, 0, width, height);
  texture->replaceRegion(region, 0, static_cast<const void *>(pixels),
                         bytes_per_row);
  stbi_image_free(pixels);
  return {};
}

}  // namespace test_app::gfx
