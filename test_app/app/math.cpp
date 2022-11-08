#include "test_app/app/math.hpp"

#include <algorithm>

namespace test_app::app {

glm::vec3 cartesian_from_spherical(const glm::vec3 &spherical) {
  float azimuthal = spherical.x;
  float polar = spherical.y;
  float radial = spherical.z;
  return glm::vec3(radial * cosf(polar) * cosf(azimuthal), radial * sinf(polar),
                   radial * cosf(polar) * sinf(azimuthal));
}

float clamp(float value, float min, float max) {
  return std::max(std::min(value, max), min);
}

float wrap(float value, float min, float max) {
  while (value < min) value += (max - min);
  while (value > max) value -= (max - min);
  return value;
}

}  // namespace test_app::app
