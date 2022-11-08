#ifndef TEST_APP_GFX_APPLE_OPENGLES_SURFACE_HPP
#define TEST_APP_GFX_APPLE_OPENGLES_SURFACE_HPP

#include <OpenGLES/OpenGLES.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <optional>

#include "glm/glm.hpp"
#include "test_app/common/error.hpp"
#include "test_app/gfx/gl/bindings.h"

namespace test_app::gfx {

class Surface {
 public:
  Surface(CA::EAGLLayer *gl_layer);
  Surface(const Surface &) = delete;
  Surface(Surface &&);
  Surface &operator=(const Surface &) = delete;
  Surface &operator=(Surface &&) = delete;
  ~Surface();

  std::optional<Error> Prepare();
  void MakeCurrent();
  void Resize(glm::uvec2 new_size);
  void Flush();

  glm::uvec2 viewport_size() const;
  GLuint frame_buffer() const;

 private:
  glm::uvec2 viewport_size_;

  GLuint frame_buffer_, color_render_buffer_, depth_render_buffer_;

  EAGL::Context *gl_context_;
  CA::EAGLLayer *gl_layer_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_APPLE_OPENGLES_SURFACE_HPP
