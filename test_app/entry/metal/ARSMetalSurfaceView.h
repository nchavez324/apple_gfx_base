#import "test_app/entry/common/ARSSurfaceView.h"

#include <QuartzCore/CAMetalLayer.h>

NS_ASSUME_NONNULL_BEGIN

@interface ARSMetalSurfaceView : ARSSurfaceView <CALayerDelegate>

@property(nonatomic) CAMetalLayer *metalLayer;

@end

NS_ASSUME_NONNULL_END
