#import "test_app/entry/uikit/ARSTAppDelegate.h"

#include "test_app/entry/common/ARSTViewController.h"

@implementation ARSTAppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions {
  self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
  self.window.rootViewController =
      [[ARSTViewController alloc] initWithBounds:UIScreen.mainScreen.bounds.size];
  [self.window makeKeyAndVisible];
  return YES;
}

@end
