#ifndef TEST_APP_GFX_CAMERA_HPP
#define TEST_APP_GFX_CAMERA_HPP

#include "glm/glm.hpp"

namespace test_app::gfx {

struct Camera {
  Camera(float field_of_view, float near_plane, float far_plane);

  glm::mat4 projection_matrix(glm::uvec2 viewport_size) const;

  float field_of_view;
  float near_plane, far_plane;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_CAMERA_HPP
