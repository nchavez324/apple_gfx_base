#include "test_app/gfx/mesh_renderer.hpp"

namespace test_app::gfx {

MeshRenderer::MeshRenderer(entt::entity mesh, entt::entity material)
    : mesh_{mesh}, material_{material} {}

entt::entity MeshRenderer::mesh() const { return mesh_; }
entt::entity MeshRenderer::material() const { return material_; }

void MeshRenderer::set_material(entt::entity material) { material_ = material; }

}  // namespace test_app::gfx
