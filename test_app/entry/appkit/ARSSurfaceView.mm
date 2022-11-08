#import "test_app/entry/appkit/ARSSurfaceView.h"

#include "test_app/input/event.hpp"

#import "test_app/entry/appkit/ARSInputRouter.h"

@implementation ARSSurfaceView {
  CVDisplayLinkRef _displayLink;
  ARSInputRouter *_inputRouter;
}

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    _inputRouter = [[ARSInputRouter alloc] init];
    NSTrackingArea *trackingArea =
        [[NSTrackingArea alloc] initWithRect:NSZeroRect
                                     options:(NSTrackingActiveWhenFirstResponder |
                                              NSTrackingMouseMoved | NSTrackingInVisibleRect)
                                       owner:self
                                    userInfo:nil];
    [self addTrackingArea:trackingArea];
  }
  return self;
}

- (void)dealloc {
  [self tearDownDisplayLink];
  [NSNotificationCenter.defaultCenter removeObserver:self];
}

#pragma mark - NSResponder

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (BOOL)becomesFirstResponder {
  return YES;
}

- (BOOL)resignFirstResponder {
  return NO;
}

- (void)keyDown:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)keyUp:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)flagsChanged:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)mouseDown:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)mouseDragged:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)mouseUp:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)rightMouseDown:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)rightMouseDragged:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)rightMouseUp:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)otherMouseDown:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)otherMouseDragged:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)otherMouseUp:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

- (void)mouseMoved:(NSEvent *)event {
  [self dispatchInputEvent:event];
}

#pragma mark - NSView

- (void)viewDidMoveToWindow {
  [super viewDidMoveToWindow];
  if ([self setupCVDisplayLinkForWindow:self.window]) {
    [self dispatchResizeIfNeeded];
  }
}

- (void)viewDidChangeBackingProperties {
  [super viewDidChangeBackingProperties];
  [self dispatchResizeIfNeeded];
}

- (void)setFrameSize:(NSSize)size {
  [super setFrameSize:size];
  [self dispatchResizeIfNeeded];
}

- (void)setBoundsSize:(NSSize)size {
  [super setBoundsSize:size];
  [self dispatchResizeIfNeeded];
}

- (void)windowWillClose:(NSNotification *)notification {
  // Stop the display link when the window is closing since there
  // is no point in drawing something that can't be seen
  if (notification.object == self.window) {
    [self tearDownDisplayLink];
  }
}

#pragma mark - CVDisplayLink

- (BOOL)setupCVDisplayLinkForWindow:(NSWindow *)window {
  [self tearDownDisplayLink];
  [NSNotificationCenter.defaultCenter removeObserver:self];

  if (!window) {
    return NO;
  }

  // Create a display link capable of being used with all active displays.
  if (CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink) != kCVReturnSuccess) {
    return NO;
  }

  // Set DispatchRenderLoop as the callback function and supply this view as the
  // argument to the callback.
  if (CVDisplayLinkSetOutputCallback(_displayLink, &DispatchRenderLoop, (__bridge void *)self) !=
      kCVReturnSuccess) {
    [self tearDownDisplayLink];
    return NO;
  }

  // Associate the display link with the display on which the view resides.
  if ([self setCurrentDisplay:_displayLink] != kCVReturnSuccess) {
    [self tearDownDisplayLink];
    return NO;
  }

  if (CVDisplayLinkStart(_displayLink) != kCVReturnSuccess) {
    [self tearDownDisplayLink];
    return NO;
  }

  // Register to be notified when the window closes so that you can stop the
  // display link.
  [NSNotificationCenter.defaultCenter addObserver:self
                                         selector:@selector(windowWillClose:)
                                             name:NSWindowWillCloseNotification
                                           object:self.window];
  [self.delegate surfaceViewDidStart];
  return YES;
}

- (CVReturn)setCurrentDisplay:(CVDisplayLinkRef)displayLink {
  CGDirectDisplayID viewDisplayID =
      (CGDirectDisplayID)[self.window.screen
                              .deviceDescription[@"NSScreenNumber"] unsignedIntegerValue];
  return CVDisplayLinkSetCurrentCGDisplay(displayLink, viewDisplayID);
}

- (void)tearDownDisplayLink {
  if (_displayLink != NULL) {
    CVDisplayLinkStop(_displayLink);
    CVDisplayLinkRelease(_displayLink);
    _displayLink = NULL;
    [self.delegate surfaceViewDidStop];
  }
}

// This is the renderer output callback function
static CVReturn DispatchRenderLoop(CVDisplayLinkRef displayLink, const CVTimeStamp *currentIn,
                                   const CVTimeStamp *nextIn, CVOptionFlags flagsIn,
                                   CVOptionFlags *flagsOut, void *displayLinkContext) {
  (void)displayLink;
  (void)flagsIn;
  (void)flagsOut;

  ARSSurfaceView *surfaceView = (__bridge ARSSurfaceView *)displayLinkContext;
  uint64_t frameTimeCurrent = currentIn->hostTime;
  uint64_t frameTimeNext = nextIn->hostTime;
  dispatch_async(dispatch_get_main_queue(), ^{
    [surfaceView.delegate surfaceViewDidVSyncAtTime:frameTimeCurrent nextTime:frameTimeNext];
  });
  return kCVReturnSuccess;
}

#pragma mark - Helper Methods

- (void)dispatchResizeIfNeeded {
  CGFloat scaleFactor = self.window.screen.backingScaleFactor;
  CGSize newSize = self.bounds.size;
  newSize.width *= scaleFactor;
  newSize.height *= scaleFactor;
  if (newSize.width <= 0 || newSize.width <= 0) {
    return;
  }
  [self.delegate surfaceViewDidResize:newSize];
}

- (void)dispatchInputEvent:(NSEvent *)event {
  [self.delegate surfaceViewDidReceiveEvent:[_inputRouter routeEvent:event]];
}

@end
