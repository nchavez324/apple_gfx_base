#import <Foundation/Foundation.h>

#include "test_app/gfx/surface.hpp"

#import "test_app/entry/common/ARSDefines.h"
#import "test_app/entry/common/ARSSurfaceView.h"

namespace test_app::entry {

class SurfaceProvider {
 public:
  SurfaceProvider(CGSize bounds);

  ARSSurfaceView *view;
  gfx::Surface surface;

  test_app::gfx::Surface CreateSurface(ARSSurfaceView *view);
};

}  // namespace test_app::entry
