#import "test_app/entry/common/ARSTViewController.h"

#include <Foundation/Foundation.hpp>
#include <chrono>
#include <memory>

#include "glm/glm.hpp"
#include "test_app/app/app.hpp"
#include "test_app/common/error.hpp"
#include "test_app/entry/common/surface_provider.h"

#import "test_app/entry/common/ARSDefines.h"
#import "test_app/entry/common/ARSSurfaceView.h"


@implementation ARSTViewController {
  CGSize _bounds;
  std::unique_ptr<test_app::app::App> _app;
}

- (instancetype)initWithBounds:(CGSize)bounds {
  self = [super init];
  if (self) {
    _bounds = bounds;
  }
  return self;
}

- (void)loadView {
  test_app::entry::SurfaceProvider surface_provider(_bounds);
  ARSSurfaceView *view = surface_provider.view;

  NS::Bundle *app_bundle = (__bridge NS::Bundle *)[NSBundle bundleForClass:[self class]];
  NS::String *resource_path_ns = app_bundle->resourcePath();
  std::filesystem::path resource_path(resource_path_ns->cString(NS::ASCIIStringEncoding));

  _app = std::make_unique<test_app::app::App>(std::move(surface_provider.surface), resource_path);

  if (auto error = _app->Prepare()) {
    [self stopAndDisplayError:*error];
    return;
  }

  view.delegate = self;
  self.view = view;
}

- (void)stopAndDisplayError:(const test_app::Error &)error {
  std::cout << error << std::endl;
  __weak __typeof(self) weakSelf = self;
  dispatch_async(dispatch_get_main_queue(), ^{
    XPBaseView *errorView = [[XPBaseView alloc] initWithFrame:weakSelf.view.frame];
#if TARGET_OS_OSX
    errorView.wantsLayer = YES;
#endif
    errorView.layer.backgroundColor = CGColorCreateGenericRGB(1, 0, 0, 1);
    weakSelf.view = errorView;
  });
}

#pragma mark - ARSSurfaceViewDelegate

- (void)surfaceViewDidStart {
  if (std::optional<test_app::Error> error = _app->Start()) {
    [self stopAndDisplayError:*error];
    return;
  }
}

- (void)surfaceViewDidVSyncAtTime:(uint64_t)frameTimeCurrent nextTime:(uint64_t)frameTimeNext {
  if (std::optional<test_app::Error> error = _app->Update(frameTimeCurrent, frameTimeNext)) {
    [self stopAndDisplayError:*error];
  }
}

- (void)surfaceViewDidResize:(CGSize)newSize {
  glm::uvec2 new_size{static_cast<unsigned int>(newSize.width),
                      static_cast<unsigned int>(newSize.height)};
  _app->Resize(new_size);
}

- (void)surfaceViewDidReceiveEvent:(test_app::input::Event *)event {
  _app->EnqueueInput(std::unique_ptr<test_app::input::Event>(event));
}

- (void)surfaceViewDidStop {
  // No-op since renderer can be kept even when display link is reset.
  _app->Stop();
}

@end
