#ifndef TEST_APP_GFX_SHADER_H
#define TEST_APP_GFX_SHADER_H

#include "test_app/common/graphics_defines.h"

#if GFX_GL
#include "test_app/gfx/gl/shader.hpp"
#elif GFX_METAL
#include "test_app/gfx/metal/shader.hpp"
#endif

#endif  // TEST_APP_GFX_SHADER_H