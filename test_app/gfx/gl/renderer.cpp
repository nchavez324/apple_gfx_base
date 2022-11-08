#include "test_app/gfx/gl/renderer.hpp"

#include <cassert>
#include <filesystem>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "test_app/common/graphics_defines.h"
#include "test_app/gfx/camera.hpp"
#include "test_app/gfx/gl/material_buffer.hpp"
#include "test_app/gfx/gl/mesh_buffer.hpp"
#include "test_app/gfx/mesh_renderer.hpp"
#include "test_app/gfx/transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace test_app::gfx {

Renderer::Renderer(std::filesystem::path resource_path)
    : mesh_observer_(),
      material_observer_(),
      resource_path_(std::move(resource_path)),
      texture_(0) {}

Renderer::Renderer(Renderer &&from)
    : mesh_observer_(),
      material_observer_(),
      resource_path_(std::move(from.resource_path_)),
      texture_(from.texture_) {
  from.mesh_observer_.disconnect();
  from.material_observer_.disconnect();
  from.texture_ = 0;
}

Renderer::~Renderer() {
  if (texture_ != 0) {
    glDeleteTextures(1, &texture_);
  }
  material_observer_.disconnect();
  mesh_observer_.disconnect();
}

std::optional<Error> Renderer::Prepare(Scene &scene, Surface &surface) {
  std::cout << "GL Renderer: " << glGetString(GL_RENDERER)
            << " GL Version: " << glGetString(GL_VERSION) << std::endl;

  auto texture = LoadTexture(resource_path_);
  if (!texture.ok()) return texture.error();
  texture_ = *texture;

  mesh_observer_.connect(scene.registry(), entt::collector.update<Mesh>());
  material_observer_.connect(scene.registry(),
                             entt::collector.update<Material>());

  return {};
}

std::optional<Error> Renderer::Draw(Scene &scene, Surface &surface) {
  surface.MakeCurrent();

  if (auto error = UploadMeshes(scene)) return error.value();
  if (auto error = UploadMaterials(scene)) return error.value();

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

  glBindFramebuffer(GL_FRAMEBUFFER, surface.frame_buffer());
  glViewport(0, 0, static_cast<GLint>(viewport_size.x),
             static_cast<GLint>(viewport_size.y));

  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

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

    glUseProgram(material_buffer.shader_program());
    // TODO: This next line and uniform location? can be moved out of draw loop.
    glUniform1i(glGetUniformLocation(material_buffer.shader_program(),
                                     "u_color_texture"),
                0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glm::mat4 model = transform.transform();
    glm::mat4 model_view_projection = projection * view * model;
    GLuint model_view_projection_uniform = glGetUniformLocation(
        material_buffer.shader_program(), "u_model_view_projection");
    glUniformMatrix4fv(model_view_projection_uniform, 1,
                       /* transpose= */ GL_FALSE,
                       glm::value_ptr(model_view_projection));
    glBindVertexArray(mesh_buffer.vertex_array());
    glDrawElements(mesh_buffer.primitive_type(), mesh_buffer.index_count(),
                   mesh_buffer.index_type(), /* offset= */ (GLvoid *)0);
  }
  glBindVertexArray(0);

  surface.Flush();

  return {};
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

std::optional<Error> Renderer::UploadMeshes(Scene &scene) {
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

  auto create_view = scene.registry().view<Mesh>(entt::exclude<MeshBuffer>);
  for (auto [entity, mesh] : create_view.each()) {
    auto buffer = MeshBuffer::Build(mesh);
    if (!buffer.ok()) return std::move(buffer.error());
    scene.registry().emplace<MeshBuffer>(entity, std::move(*buffer));
    continue;
  }

  // Modify buffer contents for updated buffers.
  for (const auto entity : mesh_observer_) {
    auto new_buffer = MeshBuffer::Build(scene.registry().get<Mesh>(entity));
    if (!new_buffer.ok()) return std::move(new_buffer.error());
    // TODO: Actually write to buffer instead of just making a new one..
    scene.registry().replace<MeshBuffer>(entity, std::move(*new_buffer));
  }
  mesh_observer_.clear();

  return std::nullopt;
}

std::optional<Error> Renderer::UploadMaterials(Scene &scene) {
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
    auto buffer = MaterialBuffer::Build(material, shader);
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
    auto new_buffer = MaterialBuffer::Build(material, shader);
    if (!new_buffer.ok()) return std::move(new_buffer.error());
    // TODO: Actually write to buffer instead of just making a new one..
    scene.registry().replace<MaterialBuffer>(entity, std::move(*new_buffer));
  }
  material_observer_.clear();

  return std::nullopt;
}

ErrorOr<GLuint> Renderer::LoadTexture(
    const std::filesystem::path &resource_path) {
  std::filesystem::path texture_path = resource_path / "texture.jpg";

  int iwidth, iheight, channels;
  stbi_uc *pixels =
      stbi_load(texture_path.c_str(), &iwidth, &iheight, &channels,
                /* desired_channels= */ STBI_rgb_alpha);
  if (!pixels) {
    return Error(ErrorCode::INVALID_ARGUMENT,
                 "Failed to load texture image: " + texture_path.string());
  }

  GLuint texture = 0;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, /* level= */ 0, GL_RGBA, iwidth, iheight,
               /* border= */ 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(pixels);
  return texture;
}

}  // namespace test_app::gfx
