#ifndef TEST_APP_GFX_MATERIAL_H
#define TEST_APP_GFX_MATERIAL_H

#include "entt/entt.hpp"

namespace test_app::gfx {

class Material {
 public:
  explicit Material(entt::entity shader);
  Material(const Material &) = delete;
  Material(Material &&) = default;
  Material &operator=(const Material &) = delete;
  Material &operator=(Material &&) = default;
  ~Material() = default;

  entt::entity shader() const;

 private:
  entt::entity shader_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_MATERIAL_H