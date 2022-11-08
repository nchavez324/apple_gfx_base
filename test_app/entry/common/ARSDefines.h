#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#define XPBaseViewController NSViewController
#define XPBaseView NSView

#elif TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#define XPBaseViewController UIViewController
#define XPBaseView UIView

#endif  // TARGET_OS_IPHONE
