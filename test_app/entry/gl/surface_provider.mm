#include "test_app/entry/common/surface_provider.h"

#include <Foundation/Foundation.hpp>

#include "test_app/gfx/gl/bindings.h"
#include "test_app/gfx/surface.hpp"

#import "test_app/entry/gl/ARSGLSurfaceView.h"

namespace test_app::entry {

SurfaceProvider::SurfaceProvider(CGSize bounds)
    : view([[ARSGLSurfaceView alloc] initWithFrame:CGRectMake(0, 0, bounds.width, bounds.height)]),
      surface(CreateSurface(view)) {}

test_app::gfx::Surface SurfaceProvider::CreateSurface(ARSSurfaceView *view) {
#if TARGET_OS_OSX
  NS::OpenGLView *gl_layer = (__bridge NS::OpenGLView *)view;
#elif TARGET_OS_IPHONE
  CAEAGLLayer *GLLayer = (CAEAGLLayer *)view.layer;
  GLLayer.opaque = YES;
  CA::EAGLLayer *gl_layer = (__bridge CA::EAGLLayer *)GLLayer;
#endif
  return test_app::gfx::Surface(gl_layer);
}

}  // namespace test_app::entry
