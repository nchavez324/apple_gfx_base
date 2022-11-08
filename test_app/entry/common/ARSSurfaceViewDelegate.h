#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

#include "test_app/input/event.hpp"

NS_ASSUME_NONNULL_BEGIN

@protocol ARSSurfaceViewDelegate
/** The surface became ready and active. */
- (void)surfaceViewDidStart;
/** The draw thread is requesting a new frame on this surface. */
- (void)surfaceViewDidVSyncAtTime:(uint64_t)frameTimeCurrent nextTime:(uint64_t)frameTimeNext;
/** The main thread is requesting a resize of this surface. */
- (void)surfaceViewDidResize:(CGSize)size;
/** The main thread received an input event. */
- (void)surfaceViewDidReceiveEvent:(test_app::input::Event *)event;
/** The surface is no longer active. */
- (void)surfaceViewDidStop;
@end

NS_ASSUME_NONNULL_END
