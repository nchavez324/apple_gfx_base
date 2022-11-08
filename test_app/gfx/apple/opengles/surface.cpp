#include "test_app/gfx/apple/opengles/surface.hpp"

namespace test_app::gfx {

Surface::Surface(CA::EAGLLayer *gl_layer)
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
  NS::Object *property_keys[] = {
      EAGL::DrawablePropertyRetainedBacking,
      EAGL::DrawablePropertyColorFormat,
  };
  NS::Object *property_values[] = {
      NS::Number::alloc()->init(false)->autorelease(),
      EAGL::ColorFormatSRGBA8,
  };
  NS::Dictionary *drawable_properties =
      NS::Dictionary::alloc()
          ->init(property_values, property_keys, 2)
          ->autorelease();
  gl_layer_->setDrawableProperties(drawable_properties);

  gl_context_ = EAGL::Context::alloc()->init(EAGL::RenderingAPIOpenGLES3);
  if (gl_context_ == nullptr) {
    return Error(ErrorCode::UNAVAILABLE, "Could not create OpenGLES context");
  }
  if (!EAGL::Context::setCurrentContext(gl_context_)) {
    return Error(ErrorCode::UNAVAILABLE, "Could not set OpenGLES context");
  }

  // In iOS & tvOS, you must create an FBO and attach a drawable texture
  // allocated by Core Animation to use as the default FBO for a view.
  glGenFramebuffers(1, &frame_buffer_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_);
  glGenRenderbuffers(1, &color_render_buffer_);
  glGenRenderbuffers(1, &depth_render_buffer_);
  Resize(glm::uvec2(0, 0));

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                            GL_RENDERBUFFER, color_render_buffer_);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, depth_render_buffer_);
  return std::nullopt;
}

void Surface::MakeCurrent() { EAGL::Context::setCurrentContext(gl_context_); }

void Surface::Resize(glm::uvec2 new_size) {
  MakeCurrent();

  assert(color_render_buffer_);
  assert(depth_render_buffer_);

  glBindRenderbuffer(GL_RENDERBUFFER, color_render_buffer_);
  gl_context_->renderbufferStorage(GL_RENDERBUFFER,
                                   static_cast<EAGL::Drawable *>(gl_layer_));
  glBindRenderbuffer(GL_RENDERBUFFER, depth_render_buffer_);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
                        static_cast<GLsizei>(new_size.x),
                        static_cast<GLsizei>(new_size.y));
  viewport_size_ = new_size;
}

void Surface::Flush() {
  glBindRenderbuffer(GL_RENDERBUFFER, color_render_buffer_);
  gl_context_->presentRenderbuffer(GL_RENDERBUFFER);
}

glm::uvec2 Surface::viewport_size() const { return viewport_size_; }

GLuint Surface::frame_buffer() const { return frame_buffer_; }

}  // namespace test_app::gfx
