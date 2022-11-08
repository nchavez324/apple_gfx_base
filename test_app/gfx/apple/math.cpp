#include "test_app/gfx/apple/math.hpp"

namespace test_app::gfx::apple::math {

namespace vector {

simd::float3 make(float x, float y, float z) { return simd::float3{x, y, z}; }

}  // namespace vector

namespace matrix {

simd::float4x4 from_glm(const glm::mat4 &mat) {
  return simd::float4x4{
      simd::float4{mat[0][0], mat[0][1], mat[0][2], mat[0][3]},
      simd::float4{mat[1][0], mat[1][1], mat[1][2], mat[1][3]},
      simd::float4{mat[2][0], mat[2][1], mat[2][2], mat[2][3]},
      simd::float4{mat[3][0], mat[3][1], mat[3][2], mat[3][3]},
  };
}

}  // namespace matrix

}  // namespace test_app::gfx::apple::math
