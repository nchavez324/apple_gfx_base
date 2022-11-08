#ifndef TEST_APP_APP_MESH_BUILDER_H
#define TEST_APP_APP_MESH_BUILDER_H

#include <memory>

#include "test_app/gfx/mesh.hpp"

namespace test_app::app {

class MeshBuilder {
 public:
  MeshBuilder() = delete;

  static gfx::Mesh Axes();
  static gfx::Mesh Cube();
  static gfx::Mesh Triplane();
};

}  // namespace test_app::app

#endif  // TEST_APP_APP_MESH_BUILDER_H
