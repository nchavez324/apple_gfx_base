#ifndef TEST_APP_GFX_SCENE_H
#define TEST_APP_GFX_SCENE_H

#include "entt/entt.hpp"

namespace test_app::gfx {

class Scene {
 public:
  Scene() = default;
  Scene(const Scene &) = delete;
  Scene(Scene &&) = default;
  Scene &operator=(const Scene &) = delete;
  Scene &operator=(Scene &&) = default;
  ~Scene() = default;

  entt::registry &registry();

 private:
  entt::registry registry_;
  /**
   * Requirements:
   * 1. The app can create or update or delete meshes
   * 2. The app can specify a transform for each mesh
   * 3. The app can specify a material (ID?) for each mesh
   * 4. The app can create or update or delete materials
   * 5. The app can specify a texture for each material
   * 6. The app can specify a vertex and fragment function for each material
   * 7. The app can specify a transform for the camera
   * 8. The app can specify parameters for the camera
   */
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_SCENE_H