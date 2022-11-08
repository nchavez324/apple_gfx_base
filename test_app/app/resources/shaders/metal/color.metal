#include <simd/simd.h>

#include <metal_stdlib>

#include "test_app/app/vertex_types.hpp"
#include "test_app/gfx/metal/uniform_types.hpp"

using namespace metal;

namespace test_app {
namespace app {
namespace color {

// Vertex shader outputs and per-fragment inputs
struct RasterizerData {
  float4 clip_space_position [[position]];
  float3 color;
};

vertex RasterizerData
vertexShader(uint vertex_id [[vertex_id]],
             constant VertexPos3Color3TexCoord2 *vertex_array
             [[buffer(test_app::gfx::VertexFunctionArgument::VERTICES)]],
             constant test_app::gfx::Uniforms &uniforms
             [[buffer(test_app::gfx::VertexFunctionArgument::UNIFORMS)]]) {
  RasterizerData out;
  out.clip_space_position = uniforms.model_view_projection *
                            float4(vertex_array[vertex_id].position, 1.0);
  out.color = vertex_array[vertex_id].color;
  return out;
}

fragment float4
fragmentShader(RasterizerData in [[stage_in]], texture2d<half> colorTexture
               [[texture(test_app::gfx::TextureArgument::COLOR)]]) {
  return float4(in.color, 1.0);
}

}  // namespace color
}  // namespace app
}  // namespace test_app
