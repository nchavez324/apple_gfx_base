#import "test_app/entry/metal/ARSMetalSurfaceView.h"

@implementation ARSMetalSurfaceView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
#if TARGET_OS_OSX
    self.wantsLayer = YES;
    self.layerContentsRedrawPolicy = NSViewLayerContentsRedrawDuringViewResize;
#endif
    _metalLayer = (CAMetalLayer *)self.layer;
    self.layer.delegate = self;
  }
  return self;
}

#pragma mark - NSView

- (CALayer *)makeBackingLayer {
  return [CAMetalLayer layer];
}

#pragma mark - UIView

+ (Class)layerClass {
  return [CAMetalLayer class];
}

@end
