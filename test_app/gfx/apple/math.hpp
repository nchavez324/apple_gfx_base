#ifndef TEST_APP_GFX_APPLE_MATH_H
#define TEST_APP_GFX_APPLE_MATH_H

#include <simd/simd.h>

#include "glm/glm.hpp"

namespace test_app::gfx::apple::math {

namespace matrix {

simd::float4x4 from_glm(const glm::mat4 &mat);

}  // namespace matrix

}  // namespace test_app::gfx::apple::math

#endif  // TEST_APP_GFX_APPLE_MATH_H
