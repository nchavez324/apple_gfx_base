#import <AppKit/AppKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <TargetConditionals.h>

#import "test_app/common/graphics_defines.h"
#import "test_app/entry/common/ARSSurfaceViewDelegate.h"

NS_ASSUME_NONNULL_BEGIN

#if GFX_GL
@interface ARSSurfaceView : NSOpenGLView
#else
@interface ARSSurfaceView : NSView
#endif

@property(nonatomic, weak, nullable) id<ARSSurfaceViewDelegate> delegate;

- (instancetype)initWithFrame:(CGRect)frame;

- (CVReturn)setCurrentDisplay:(CVDisplayLinkRef)displayLink;

@end

NS_ASSUME_NONNULL_END
