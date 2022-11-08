#import "test_app/entry/appkit/ARSTAppDelegate.h"

#include "test_app/entry/common/ARSTViewController.h"

@implementation ARSTAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  self.window =
      [[NSWindow alloc] initWithContentRect:CGRectZero
                                  styleMask:NSWindowStyleMaskClosable | NSWindowStyleMaskResizable |
                                            NSWindowStyleMaskTitled
                                    backing:NSBackingStoreBuffered
                                      defer:YES];
  self.window.title = @"Aerospike Test App";
  self.window.contentViewController =
      [[ARSTViewController alloc] initWithBounds:CGSizeMake(800, 600)];

  [NSApp activateIgnoringOtherApps:YES];
  [self.window center];
  [self.window makeKeyAndOrderFront:nil];
  [self.window makeFirstResponder:self.window.contentViewController.view];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app {
  return YES;
}

@end
