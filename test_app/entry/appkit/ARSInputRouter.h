#import <AppKit/AppKit.h>

#include "test_app/input/event.hpp"

NS_ASSUME_NONNULL_BEGIN

@interface ARSInputRouter : NSObject

- (test_app::input::Event *)routeEvent:(NSEvent *)event;

@end

NS_ASSUME_NONNULL_END
