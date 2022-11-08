#include "test_app/gfx/metal/material_buffer.hpp"

#include "test_app/gfx/apple/error.hpp"

namespace test_app::gfx {

ErrorOr<MaterialBuffer> MaterialBuffer::Build(MTL::Device *device,
                                              MTL::PixelFormat format_color,
                                              MTL::PixelFormat format_depth,
                                              const Material &material,
                                              const Shader &shader) {
  auto library = NewShaderLibrary(device, shader.library_path());
  if (!library.ok()) return library.error();
  (*library)->autorelease();

  auto vertex_function =
      NewShaderFunction(*library, shader.vertex_function_name());
  if (!vertex_function.ok()) return vertex_function.error();
  (*vertex_function)->autorelease();

  auto fragment_function =
      NewShaderFunction(*library, shader.fragment_function_name());
  if (!fragment_function.ok()) return fragment_function.error();
  (*fragment_function)->autorelease();

  MTL::RenderPipelineDescriptor *pipeline_descriptor =
      MTL::RenderPipelineDescriptor::alloc()->init()->autorelease();
  NS::String *pipeline_label =
      NS::String::alloc()
          ->init("RenderPipeline", NS::ASCIIStringEncoding)
          ->autorelease();
  pipeline_descriptor->setLabel(pipeline_label);
  pipeline_descriptor->setVertexFunction(*vertex_function);
  pipeline_descriptor->setFragmentFunction(*fragment_function);
  pipeline_descriptor->colorAttachments()->object(0)->setPixelFormat(
      format_color);
  pipeline_descriptor->setDepthAttachmentPixelFormat(format_depth);

  NS::Error *error = nullptr;
  MTL::RenderPipelineState *pipeline_state =
      device->newRenderPipelineState(pipeline_descriptor, &error)
          ->autorelease();
  if (pipeline_state == nullptr || error != nullptr) {
    return apple::errorFromNSError(error);
  }

  return MaterialBuffer(pipeline_state);
}

MaterialBuffer::MaterialBuffer(MTL::RenderPipelineState *render_pipeline_state)
    : render_pipeline_state_{render_pipeline_state->retain()} {}

MaterialBuffer::MaterialBuffer(MaterialBuffer &&from)
    : render_pipeline_state_{from.render_pipeline_state_} {
  from.render_pipeline_state_ = nullptr;
}

MaterialBuffer &MaterialBuffer::operator=(MaterialBuffer &&from) {
  this->render_pipeline_state_ = from.render_pipeline_state_;
  from.render_pipeline_state_ = nullptr;
  return *this;
}

MaterialBuffer::~MaterialBuffer() {
  if (render_pipeline_state_ != nullptr) render_pipeline_state_->release();
}

MTL::RenderPipelineState *MaterialBuffer::render_pipeline_state() {
  return render_pipeline_state_;
}

ErrorOr<MTL::Library *> MaterialBuffer::NewShaderLibrary(
    MTL::Device *device, const std::filesystem::path &path) {
  NS::String *path_ns = NS::String::alloc()
                            ->init(path.c_str(), NS::ASCIIStringEncoding)
                            ->autorelease();

  NS::Error *error = nullptr;
  MTL::Library *shader_library = device->newLibrary(path_ns, &error);
  if (shader_library == nullptr || error != nullptr) {
    return apple::errorFromNSError(error);
  }

  return shader_library;
}

ErrorOr<MTL::Function *> MaterialBuffer::NewShaderFunction(
    MTL::Library *library, const std::string &function_name) {
  NS::String *function_name_ns =
      NS::String::alloc()
          ->init(function_name.c_str(), NS::ASCIIStringEncoding)
          ->autorelease();
  MTL::FunctionConstantValues *constant_values =
      MTL::FunctionConstantValues::alloc()->init()->autorelease();

  NS::Error *error = nullptr;
  MTL::Function *function =
      library->newFunction(function_name_ns, constant_values, &error);
  if (function == nullptr || error != nullptr) {
    return apple::errorFromNSError(error);
  }

  return function;
}

}  // namespace test_app::gfx