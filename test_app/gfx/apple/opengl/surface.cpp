#include "test_app/gfx/apple/opengl/surface.hpp"

namespace test_app::gfx {

Surface::Surface(NS::OpenGLView *gl_layer)
    : viewport_size_(0, 0),
      frame_buffer_(0),
      color_render_buffer_(0),
      depth_render_buffer_(0),
      gl_context_(nullptr),
      gl_layer_(gl_layer->retain()) {}

Surface::Surface(Surface &&from)
    : viewport_size_(from.viewport_size_),
      frame_buffer_(from.frame_buffer_),
      color_render_buffer_(from.color_render_buffer_),
      depth_render_buffer_(from.depth_render_buffer_),
      gl_context_(from.gl_context_),
      gl_layer_(from.gl_layer_) {
  from.viewport_size_ = glm::uvec2(0, 0);
  from.frame_buffer_ = 0;
  from.color_render_buffer_ = 0;
  from.depth_render_buffer_ = 0;
  from.gl_context_ = nullptr;
  from.gl_layer_ = nullptr;
}

Surface::~Surface() {
  if (depth_render_buffer_ != 0) {
    glDeleteBuffers(1, &depth_render_buffer_);
  }
  if (color_render_buffer_ != 0) {
    glDeleteBuffers(1, &color_render_buffer_);
  }
  if (frame_buffer_ != 0) {
    glDeleteBuffers(1, &frame_buffer_);
  }
  gl_context_->release();
  gl_layer_->release();
}

std::optional<Error> Surface::Prepare() {
  NS::OpenGLPixelFormatAttribute pixel_format_attributes[] = {
      NS::OpenGLPFAColorSize,          32, NS::OpenGLPFADoubleBuffer,
      NS::OpenGLPFADepthSize,          24, NS::OpenGLPFAOpenGLProfile,
      NS::OpenGLProfileVersion3_2Core, 0,
  };
  NS::OpenGLPixelFormat *pixel_format = NS::OpenGLPixelFormat::alloc()
                                            ->init(pixel_format_attributes)
                                            ->autorelease();
  if (pixel_format == nullptr) {
    return Error(ErrorCode::NOT_FOUND, "No OpenGL pixel format");
  }

  gl_context_ = NS::OpenGLContext::alloc()->init(pixel_format,
                                                 /* share_context= */ nullptr);
  MakeCurrent();
  glEnable(GL_FRAMEBUFFER_SRGB);

  gl_layer_->setPixelFormat(pixel_format);
  gl_layer_->setOpenGLContext(gl_context_);
  gl_layer_->setWantsBestResolutionOpenGLSurface(true);

  // The default framebuffer object (FBO) is 0 on macOS, because it uses a
  // traditional OpenGL pixel format model.
  frame_buffer_ = 0;
  return std::nullopt;
}

void Surface::MakeCurrent() { gl_context_->makeCurrentContext(); }

void Surface::Resize(glm::uvec2 new_size) { viewport_size_ = new_size; }

void Surface::Flush() { gl_context_->flushBuffer(); }

glm::uvec2 Surface::viewport_size() const { return viewport_size_; }

GLuint Surface::frame_buffer() const { return frame_buffer_; }

}  // namespace test_app::gfx
