#ifndef TEST_APP_GFX_MESH_RENDERER_H
#define TEST_APP_GFX_MESH_RENDERER_H

#include "entt/entt.hpp"

namespace test_app::gfx {

/**
 * Roughly, represents a "draw" of a given Mesh component, using the given
 * Material. If not pointing to a valid Mesh, then this does nothing.
 */
class MeshRenderer {
 public:
  MeshRenderer(entt::entity mesh, entt::entity material);
  MeshRenderer(const MeshRenderer &) = delete;
  MeshRenderer(MeshRenderer &&) = default;
  MeshRenderer &operator=(const MeshRenderer &) = delete;
  MeshRenderer &operator=(MeshRenderer &&) = default;
  ~MeshRenderer() = default;

  entt::entity mesh() const;
  entt::entity material() const;

  void set_material(entt::entity);

 private:
  entt::entity mesh_;
  entt::entity material_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_MESH_RENDERER_H