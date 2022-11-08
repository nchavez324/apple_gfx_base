#ifndef TEST_APP_GFX_SURFACE_H
#define TEST_APP_GFX_SURFACE_H

#include "test_app/common/platform_defines.h"

#if PLATFORM_APPLE
#include "test_app/gfx/apple/surface.hpp"
#endif

// +X is right, +Y is up, +Z is into the screen, the LH convention. This is
// for all graphics APIs, since this is tweaked in GenerateUniforms.

#endif  // TEST_APP_GFX_SURFACE_H
