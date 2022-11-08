#include "test_app/gfx/scene.hpp"

namespace test_app::gfx {

entt::registry &Scene::registry() { return registry_; }

}  // namespace test_app::gfx