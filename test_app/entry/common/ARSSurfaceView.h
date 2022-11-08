#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import "test_app/entry/appkit/ARSSurfaceView.h"
#elif TARGET_OS_IPHONE
#import "test_app/entry/uikit/ARSSurfaceView.h"
#endif
