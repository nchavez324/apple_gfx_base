#import "examples/main.h"

#import <AppKit/AppKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
  CGRect windowRect = CGRectMake(0, 0, 800, 600);
  NSWindowStyleMask windowStyle = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
                                  NSWindowStyleMaskResizable | NSWindowStyleMaskTitled;
  NSWindow* window = [[NSWindow alloc] initWithContentRect:windowRect
                                                 styleMask:windowStyle
                                                   backing:NSBackingStoreBuffered
                                                     defer:YES];
  window.title = @"Apple Gfx Base Example App";
  window.restorable = YES;
  window.contentViewController = [[ViewController alloc] init];

  [NSApp activateIgnoringOtherApps:YES];
  [window center];
  [window makeKeyAndOrderFront:nil];
  [window makeFirstResponder:window.contentViewController];

  self.window = window;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app {
  return YES;
}

- (void)applicationWillTerminate:(NSNotification*)notification {
}

@end

@implementation ViewController

- (instancetype)init {
  self = [super init];
  return self;
}

#pragma mark - NSViewController

- (void)loadView {
  NSView* view = [[NSView alloc] initWithFrame:CGRectMake(0, 0, 800, 600)];
  view.wantsLayer = YES;
  view.layer.backgroundColor = CGColorCreateGenericRGB(1, 0, 0, 1);
  self.view = view;
}

@end

int main(int argc, char* argv[]) {
  NSApplication* app = NSApplication.sharedApplication;
  AppDelegate* appDelegate = [[AppDelegate alloc] init];
  app.delegate = appDelegate;
  return NSApplicationMain(argc, (const char* _Nonnull* _Nonnull)argv);
}
