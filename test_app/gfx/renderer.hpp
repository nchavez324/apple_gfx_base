#ifndef TEST_APP_GFX_RENDERER_HPP
#define TEST_APP_GFX_RENDERER_HPP

#include "test_app/common/graphics_defines.h"

#if GFX_GL
#include "test_app/gfx/gl/renderer.hpp"
#elif GFX_METAL
#include "test_app/gfx/metal/renderer.hpp"
#endif

#endif  // TEST_APP_GFX_RENDERER_HPP
