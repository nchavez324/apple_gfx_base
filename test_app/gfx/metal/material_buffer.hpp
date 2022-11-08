#ifndef TEST_APP_GFX_METAL_MATERIAL_BUFFER_H
#define TEST_APP_GFX_METAL_MATERIAL_BUFFER_H

#include <optional>

#include "test_app/common/error_or.hpp"
#include "test_app/gfx/material.hpp"
#include "test_app/gfx/shader.hpp"
#include "third_party/apple_cpp/Metal/Metal.hpp"

namespace test_app::gfx {

/**
 * The Metal GPU representation of material data. Internally, the Renderer will
 * create a MaterialBuffer component for each Material component.
 * To use this material to draw, a MeshRenderer component must be pointing to
 * the entity with this component.
 */
class MaterialBuffer {
 public:
  static ErrorOr<MaterialBuffer> Build(MTL::Device *device,
                                       MTL::PixelFormat format_color,
                                       MTL::PixelFormat format_depth,
                                       const Material &material,
                                       const Shader &shader);

  MaterialBuffer(MTL::RenderPipelineState *render_pipeline_state);
  MaterialBuffer(const MaterialBuffer &) = delete;
  MaterialBuffer(MaterialBuffer &&);
  MaterialBuffer &operator=(const MaterialBuffer &) = delete;
  MaterialBuffer &operator=(MaterialBuffer &&);
  ~MaterialBuffer();

  MTL::RenderPipelineState *render_pipeline_state();

 private:
  MTL::RenderPipelineState *render_pipeline_state_;

  static ErrorOr<MTL::Library *> NewShaderLibrary(
      MTL::Device *device, const std::filesystem::path &path);
  static ErrorOr<MTL::Function *> NewShaderFunction(
      MTL::Library *library, const std::string &function_name);
};
}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_METAL_MATERIAL_BUFFER_H
