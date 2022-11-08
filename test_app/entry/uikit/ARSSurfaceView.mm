#import "test_app/entry/uikit/ARSSurfaceView.h"

@interface ARSSurfaceView ()
@property(nonatomic, getter=isPaused) BOOL paused;
@end

@implementation ARSSurfaceView {
  CADisplayLink *_displayLink;
  NSThread *_renderThread;
  BOOL _continueRunLoop;
}

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    [NSNotificationCenter.defaultCenter addObserver:self
                                           selector:@selector(didEnterBackground:)
                                               name:UIApplicationDidEnterBackgroundNotification
                                             object:UIApplication.sharedApplication];
    [NSNotificationCenter.defaultCenter addObserver:self
                                           selector:@selector(willEnterForeground:)
                                               name:UIApplicationWillEnterForegroundNotification
                                             object:UIApplication.sharedApplication];
  }
  return self;
}

- (void)dealloc {
  [self tearDownDisplayLink];
  [NSNotificationCenter.defaultCenter removeObserver:self];
}

#pragma mark - UIView

- (void)didMoveToWindow {
  [super didMoveToWindow];

  if (![self setupCADisplayLinkForWindow:self.window]) {
    return;
  }
  [self startRenderThread];
  [self dispatchResizeIfNeeded];
}

- (void)setContentScaleFactor:(CGFloat)contentScaleFactor {
  [super setContentScaleFactor:contentScaleFactor];
  [self dispatchResizeIfNeeded];
}

- (void)layoutSubviews {
  [super layoutSubviews];
  [self dispatchResizeIfNeeded];
}

- (void)setFrame:(CGRect)frame {
  [super setFrame:frame];
  [self dispatchResizeIfNeeded];
}

- (void)setBounds:(CGRect)bounds {
  [super setBounds:bounds];
  [self dispatchResizeIfNeeded];
}

- (void)didEnterBackground:(NSNotification *)notification {
  self.paused = YES;
}

- (void)willEnterForeground:(NSNotification *)notification {
  self.paused = NO;
}

#pragma mark - Accessors

- (BOOL)paused {
  return _paused;
}

- (void)setPaused:(BOOL)paused {
  _paused = paused;
  _displayLink.paused = paused;
}

#pragma mark - CADisplayLink

- (BOOL)setupCADisplayLinkForWindow:(UIWindow *)window {
  [self tearDownDisplayLink];
  if (!window) {
    return NO;
  }
  self.contentScaleFactor = UIScreen.mainScreen.nativeScale;
  _displayLink = [window.screen displayLinkWithTarget:self selector:@selector(dispatchRequestDraw)];
  _displayLink.paused = self.paused;
  _displayLink.preferredFramesPerSecond = 60;
  [self.delegate surfaceViewDidStart];
  return YES;
}

- (void)tearDownDisplayLink {
  if (_displayLink != nil) {
    [_displayLink invalidate];
    _displayLink = nil;
    [self.delegate surfaceViewDidStop];
  }
}

#pragma mark - Render Thread

- (void)startRenderThread {
  // Protect _continueRunLoop with a `@synchronized` block since it is accessed
  // by the separate animation thread.
  @synchronized(self) {
    // Stop animation loop allowing the loop to complete if it's in progress.
    _continueRunLoop = NO;
  }
  // Create and start a secondary NSThread which will have another run runloop.
  // The NSThread class will call the 'runThread' method at the start of the
  // secondary thread's execution.
  _renderThread = [[NSThread alloc] initWithTarget:self selector:@selector(runThread) object:nil];
  _continueRunLoop = YES;
  [_renderThread start];
}

- (void)runThread {
  // Set the display link to the run loop of this thread so its call back occurs
  // on this thread
  NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
  [_displayLink addToRunLoop:runLoop forMode:@"ARSDisplayLinkMode"];
  // The '_continueRunLoop' ivar is set outside this thread, so it must be
  // synchronized. Create a 'continueRunLoop' local var that can be set from the
  // _continueRunLoop ivar in a @synchronized block.
  BOOL continueRunLoop = YES;

  while (continueRunLoop) {
    // Create autorelease pool for the current iteration of loop.
    @autoreleasepool {
      // Run the loop each frame accepting input only from the display link.
      [runLoop runMode:@"ARSDisplayLinkMode" beforeDate:[NSDate distantFuture]];
    }
    // Synchronize this with the _continueRunLoop ivar which is set on another
    // thread.
    @synchronized(self) {
      // Anything accessed outside the thread such as the '_continueRunLoop'
      // ivar is read inside the synchronized block to ensure it is
      // fully/atomically written.
      continueRunLoop = _continueRunLoop;
    }
  }
}

- (void)dispatchRequestDraw {
  CFTimeInterval timestamp = _displayLink.timestamp;
  CFTimeInterval targetTimestamp = _displayLink.targetTimestamp;
  uint64_t frameTimeCurrent = (uint64_t)(timestamp * 1000000000);
  uint64_t frameTimeNext = (uint64_t)(targetTimestamp * 1000000000);
  // TODO: See if there's simpler way to get notified on main queue
  dispatch_async(dispatch_get_main_queue(), ^{
    [self.delegate surfaceViewDidVSyncAtTime:frameTimeCurrent nextTime:frameTimeNext];
  });
}

#pragma mark - Helper Methods

- (void)dispatchResizeIfNeeded {
  CGFloat scaleFactor = self.window.screen.nativeScale;
  CGSize newSize = self.bounds.size;
  newSize.width *= scaleFactor;
  newSize.height *= scaleFactor;
  if (newSize.width <= 0 || newSize.width <= 0) {
    return;
  }
  [self.delegate surfaceViewDidResize:newSize];
}

@end
