#include "test_app/gfx/apple/metal/surface.hpp"

namespace test_app::gfx {

static const MTL::ClearColor kColorClear(0.5f, 0.5f, 0.5f, 1.0f);
static const MTL::PixelFormat kPixelFormatDraw =
    MTL::PixelFormatBGRA8Unorm_sRGB;
static const MTL::PixelFormat kPixelFormatDepth = MTL::PixelFormatDepth32Float;

Surface::Surface(CA::MetalLayer *layer, MTL::Device *device)
    : viewport_size_(0, 0),
      layer_(layer->retain()),
      device_(device->retain()),
      drawable_render_descriptor_(nullptr),
      depth_stencil_state_(nullptr),
      depth_target_(nullptr) {}

Surface::Surface(Surface &&from)
    : viewport_size_(from.viewport_size_),
      layer_(from.layer_),
      device_(from.device_),
      drawable_render_descriptor_(from.drawable_render_descriptor_),
      depth_stencil_state_(from.depth_stencil_state_),
      depth_target_(from.depth_target_) {
  from.viewport_size_ = glm::uvec2(0, 0);
  from.layer_ = nullptr;
  from.device_ = nullptr;
  from.drawable_render_descriptor_ = nullptr;
  from.depth_stencil_state_ = nullptr;
  from.depth_target_ = nullptr;
}

Surface::~Surface() {
  depth_target_->release();
  depth_stencil_state_->release();
  drawable_render_descriptor_->release();
  device_->release();
  layer_->release();
}

std::optional<Error> Surface::Prepare() {
  layer_->setDevice(device_);
  layer_->setPixelFormat(kPixelFormatDraw);

  drawable_render_descriptor_ = MTL::RenderPassDescriptor::alloc()->init();
  drawable_render_descriptor_->colorAttachments()->object(0)->setLoadAction(
      MTL::LoadActionClear);
  drawable_render_descriptor_->colorAttachments()->object(0)->setStoreAction(
      MTL::StoreActionStore);
  drawable_render_descriptor_->colorAttachments()->object(0)->setClearColor(
      kColorClear);

  drawable_render_descriptor_->depthAttachment()->setLoadAction(
      MTL::LoadActionClear);
  drawable_render_descriptor_->depthAttachment()->setStoreAction(
      MTL::StoreActionDontCare);
  drawable_render_descriptor_->depthAttachment()->setClearDepth(1);

  auto depth_descriptor =
      MTL::DepthStencilDescriptor::alloc()->init()->autorelease();
  depth_descriptor->setDepthCompareFunction(MTL::CompareFunctionLessEqual);
  depth_descriptor->setDepthWriteEnabled(true);
  depth_stencil_state_ = device_->newDepthStencilState(depth_descriptor);
  if (depth_stencil_state_ == nullptr) {
    return Error(ErrorCode::UNAVAILABLE,
                 "Could not create depth stencil state");
  }

  return std::nullopt;
}

void Surface::Resize(glm::uvec2 new_size) {
  CG::Size old_size = layer_->drawableSize();
  if (new_size.x == old_size.width && new_size.y == old_size.height) {
    return;
  }

  layer_->setDrawableSize(CG::Size(new_size.x, new_size.y));
  viewport_size_ = new_size;

  MTL::TextureDescriptor *depth_target_descriptor =
      MTL::TextureDescriptor::alloc()->init()->autorelease();
  depth_target_descriptor->setWidth(new_size.x);
  depth_target_descriptor->setHeight(new_size.y);
  depth_target_descriptor->setPixelFormat(kPixelFormatDepth);
  depth_target_descriptor->setStorageMode(MTL::StorageModePrivate);
  depth_target_descriptor->setUsage(MTL::TextureUsageRenderTarget);

  depth_target_->release();
  depth_target_ = device_->newTexture(depth_target_descriptor);
  drawable_render_descriptor_->depthAttachment()->setTexture(depth_target_);
}

glm::uvec2 Surface::viewport_size() const { return viewport_size_; }
CA::MetalLayer *Surface::layer() { return layer_; }
MTL::Device *Surface::device() { return device_; }
MTL::RenderPassDescriptor *Surface::drawable_render_descriptor() {
  return drawable_render_descriptor_;
}
MTL::DepthStencilState *Surface::depth_stencil_state() {
  return depth_stencil_state_;
}
MTL::PixelFormat Surface::pixel_format_draw() const { return kPixelFormatDraw; }
MTL::PixelFormat Surface::pixel_format_depth() const {
  return kPixelFormatDepth;
}

}  // namespace test_app::gfx
