#include "test_app/app/mesh_builder.hpp"

#include "test_app/app/vertex_types.hpp"
#include "test_app/gfx/primitive.hpp"
#include "test_app/gfx/vertex_descriptor.hpp"
#include "test_app/gfx/vertex_member.hpp"
#include "test_app/gfx/vertex_member_type.hpp"

namespace test_app::app {

static const std::vector<VertexPos3Color3TexCoord2> kAxesUnitVertices = {
    // LHS
    // +X
    {{0, 0, 0}, {1, 0, 0}, {0, 0}},
    {{+1, 0, 0}, {1, 0, 0}, {0, 0}},
    // -X
    {{0, 0, 0}, {0, 1, 1}, {0, 0}},
    {{-1, 0, 0}, {0, 1, 1}, {0, 0}},

    // +Y
    {{0, 0, 0}, {0, 1, 0}, {0, 0}},
    {{0, +1, 0}, {0, 1, 0}, {0, 0}},
    // -Y
    {{0, 0, 0}, {1, 0, 1}, {0, 0}},
    {{0, -1, 0}, {1, 0, 1}, {0, 0}},

    // +Z
    {{0, 0, 0}, {0, 0, 1}, {0, 0}},
    {{0, 0, +1}, {0, 0, 1}, {0, 0}},
    // -Z
    {{0, 0, 0}, {1, 1, 0}, {0, 0}},
    {{0, 0, -1}, {1, 1, 0}, {0, 0}},
};
static const std::vector<uint16_t> kAxesTriangles = {0, 1, 2, 3, 4,  5,
                                                     6, 7, 8, 9, 10, 11};

static const std::vector<VertexPos3Color3TexCoord2> kCubeVertices = {
    // +X face
    {{+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{+0.5f, +0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    // -X face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, +0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, +0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{-0.5f, +0.5f, +0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
};
static const std::vector<uint16_t> kCubeTriangles = {
    // +X face
    0,
    1,
    2,
    1,
    3,
    2,
    // +Y face
    6,
    2,
    7,
    2,
    3,
    7,
    // +Z face
    1,
    5,
    3,
    5,
    7,
    3,
    // -X face
    5,
    4,
    7,
    4,
    6,
    7,
    // -Y face
    5,
    1,
    4,
    1,
    0,
    4,
    // -Z face
    4,
    0,
    6,
    0,
    2,
    6,

};

static const std::vector<VertexPos3Color3TexCoord2> kTriplaneUnitVertices = {
    // LHS
    // YZ plane, +X
    {{+0.0f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{+0.0f, -0.5f, +0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{+0.0f, +0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{+0.0f, +0.5f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

    // XZ plane, +Y
    {{-0.5f, +0.0f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{+0.5f, +0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, +0.0f, +0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{+0.5f, +0.0f, +0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

    // XY plane, +Z
    {{-0.5f, -0.5f, +0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{+0.5f, -0.5f, +0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{-0.5f, +0.5f, +0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{+0.5f, +0.5f, +0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
};
static const std::vector<uint16_t> kTriplaneTriangles = {
    0, 1, 2, 1, 3, 2, 4, 5, 6, 5, 7, 6, 8, 9, 10, 9, 11, 10,
};

gfx::Mesh MeshBuilder::Axes() {
  return gfx::Mesh(gfx::Primitive(gfx::PrimitiveType::LINE, sizeof(uint16_t),
                                  kAxesTriangles.size(), kAxesTriangles.data()),
                   VertexPos3Color3TexCoord2::vertex_descriptor(),
                   kAxesUnitVertices.size(), kAxesUnitVertices.data());
}

gfx::Mesh MeshBuilder::Cube() {
  return gfx::Mesh(
      gfx::Primitive(gfx::PrimitiveType::TRIANGLE, sizeof(uint16_t),
                     kCubeTriangles.size(), kCubeTriangles.data()),
      VertexPos3Color3TexCoord2::vertex_descriptor(), kCubeVertices.size(),
      kCubeVertices.data());
}

gfx::Mesh MeshBuilder::Triplane() {
  return gfx::Mesh(
      gfx::Primitive(gfx::PrimitiveType::TRIANGLE, sizeof(uint16_t),
                     kTriplaneTriangles.size(), kTriplaneTriangles.data()),
      VertexPos3Color3TexCoord2::vertex_descriptor(),
      kTriplaneUnitVertices.size(), kTriplaneUnitVertices.data());
}

}  // namespace test_app::app
