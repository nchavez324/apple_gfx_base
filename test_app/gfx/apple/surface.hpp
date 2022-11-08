#ifndef TEST_APP_GFX_APPLE_SURFACE_H
#define TEST_APP_GFX_APPLE_SURFACE_H

#include "test_app/common/graphics_defines.h"

#if GFX_OPEN_GL
#include "test_app/gfx/apple/opengl/surface.hpp"
#elif GFX_OPEN_GLES
#include "test_app/gfx/apple/opengles/surface.hpp"
#elif GFX_METAL
#include "test_app/gfx/apple/metal/surface.hpp"
#endif

#endif  // TEST_APP_GFX_APPLE_SURFACE_H
