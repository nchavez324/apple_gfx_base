#ifndef TEST_APP_APP_VERTEX_TYPES_2_H
#define TEST_APP_APP_VERTEX_TYPES_2_H

#include <simd/simd.h>

#if !defined(__METAL_VERSION__)
#include "test_app/gfx/vertex_descriptor.hpp"
#include "test_app/gfx/vertex_member.hpp"
#include "test_app/gfx/vertex_member_type.hpp"
#endif  // !defined(__METAL_VERSION__)

namespace test_app {
namespace app {

struct VertexPos3Color3 {
  simd::float3 position;
  simd::float3 color;

#if !defined(__METAL_VERSION__)
  static const gfx::VertexDescriptor &vertex_descriptor() {
    static gfx::VertexDescriptor vertex_descriptor(
        std::vector<gfx::VertexMember>{
            {gfx::VertexMemberType::FLOAT, 3,
             offsetof(VertexPos3Color3, position)},
            {gfx::VertexMemberType::FLOAT, 3,
             offsetof(VertexPos3Color3, color)},
        },
        sizeof(VertexPos3Color3));
    return vertex_descriptor;
  }
#endif  // !defined(__METAL_VERSION__)
};

struct VertexPos3Color3TexCoord2 {
  simd::float3 position;
  simd::float3 color;
  simd::float2 tex_coord;

#if !defined(__METAL_VERSION__)
  static const gfx::VertexDescriptor &vertex_descriptor() {
    static gfx::VertexDescriptor vertex_descriptor(
        std::vector<gfx::VertexMember>{
            {gfx::VertexMemberType::FLOAT, 3,
             offsetof(VertexPos3Color3TexCoord2, position)},
            {gfx::VertexMemberType::FLOAT, 3,
             offsetof(VertexPos3Color3TexCoord2, color)},
            {gfx::VertexMemberType::FLOAT, 2,
             offsetof(VertexPos3Color3TexCoord2, tex_coord)},
        },
        sizeof(VertexPos3Color3TexCoord2));
    return vertex_descriptor;
  }
#endif  // !defined(__METAL_VERSION__)
};

}  // namespace app
}  // namespace test_app

#endif  // TEST_APP_APP_VERTEX_TYPES_2_H
