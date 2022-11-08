#import <Cocoa/Cocoa.h>

#import "test_app/entry/appkit/ARSTAppDelegate.h"

int main(int argc, const char *argv[]) {
  NSApplication *app = NSApplication.sharedApplication;
  ARSTAppDelegate *appDelegate = [[ARSTAppDelegate alloc] init];
  app.delegate = appDelegate;
  return NSApplicationMain(argc, argv);
}
