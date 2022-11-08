#ifndef TEST_APP_GFX_APPLE_METAL_SURFACE_HPP
#define TEST_APP_GFX_APPLE_METAL_SURFACE_HPP

#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <optional>

#include "glm/glm.hpp"
#include "test_app/common/error.hpp"

namespace test_app::gfx {

class Surface {
 public:
  Surface(CA::MetalLayer *layer, MTL::Device *device);
  Surface(const Surface &) = delete;
  Surface(Surface &&);
  Surface &operator=(const Surface &) = delete;
  Surface &operator=(Surface &&) = delete;
  ~Surface();

  std::optional<Error> Prepare();
  void Resize(glm::uvec2 new_size);

  glm::uvec2 viewport_size() const;
  CA::MetalLayer *layer();
  MTL::Device *device();
  MTL::RenderPassDescriptor *drawable_render_descriptor();
  MTL::DepthStencilState *depth_stencil_state();

  MTL::PixelFormat pixel_format_draw() const;
  MTL::PixelFormat pixel_format_depth() const;

 private:
  glm::uvec2 viewport_size_;

  CA::MetalLayer *layer_;
  MTL::Device *device_;
  MTL::RenderPassDescriptor *drawable_render_descriptor_;
  MTL::DepthStencilState *depth_stencil_state_;
  MTL::Texture *depth_target_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_APPLE_METAL_SURFACE_HPP
