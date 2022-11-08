#ifndef TEST_APP_GFX_METAL_UNIFORM_TYPES_H
#define TEST_APP_GFX_METAL_UNIFORM_TYPES_H

#include <simd/simd.h>

namespace test_app {
namespace gfx {

enum class VertexFunctionArgument {
  VERTICES = 0,
  UNIFORMS = 1,
};

enum class TextureArgument {
  COLOR = 0,
};

struct Uniforms {
  simd::float4x4 model_view_projection;
};

}  // namespace gfx
}  // namespace test_app

#endif  // TEST_APP_GFX_METAL_UNIFORM_TYPES_H
