#include "test_app/gfx/material.hpp"

namespace test_app::gfx {

Material::Material(entt::entity shader) : shader_{shader} {}

entt::entity Material::shader() const { return shader_; }

}  // namespace test_app::gfx
