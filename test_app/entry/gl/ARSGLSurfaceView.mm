#import "test_app/entry/gl/ARSGLSurfaceView.h"

@implementation ARSGLSurfaceView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.layer.delegate = self;
  }
  return self;
}

#pragma mark - NSView

#if TARGET_OS_OSX
- (CVReturn)setCurrentDisplay:(CVDisplayLinkRef)displayLink {
  return CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(
      displayLink, self.openGLContext.CGLContextObj,
      self.openGLContext.pixelFormat.CGLPixelFormatObj);
}
#endif

#pragma mark - UIView

#if TARGET_OS_IPHONE
+ (Class)layerClass {
  return [CAEAGLLayer class];
}
#endif

@end
