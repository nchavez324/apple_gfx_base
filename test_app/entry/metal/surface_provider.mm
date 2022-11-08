#include "test_app/entry/common/surface_provider.h"

#include <Foundation/Foundation.hpp>

#include "test_app/gfx/surface.hpp"

#import "test_app/entry/metal/ARSMetalSurfaceView.h"

namespace test_app::entry {

SurfaceProvider::SurfaceProvider(CGSize bounds)
    : view([[ARSMetalSurfaceView alloc]
          initWithFrame:CGRectMake(0, 0, bounds.width, bounds.height)]),
      surface(CreateSurface(view)) {}

test_app::gfx::Surface SurfaceProvider::CreateSurface(ARSSurfaceView *view) {
  ARSMetalSurfaceView *metalView = (ARSMetalSurfaceView *)view;
  CA::MetalLayer *layer = (__bridge CA::MetalLayer *)metalView.metalLayer;
  MTL::Device *device = MTL::CreateSystemDefaultDevice();
  return test_app::gfx::Surface(layer, device);
}

}  // namespace test_app::entry
