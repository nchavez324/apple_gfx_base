#include "test_app/gfx/camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace test_app::gfx {

Camera::Camera(float field_of_view, float near_plane, float far_plane)
    : field_of_view(field_of_view),
      near_plane(near_plane),
      far_plane(far_plane) {}

glm::mat4 Camera::projection_matrix(glm::uvec2 viewport_size) const {
  float aspect_ratio = static_cast<float>(viewport_size.x) / viewport_size.y;
  return glm::perspective(field_of_view, aspect_ratio, near_plane, far_plane);
}

}  // namespace test_app::gfx