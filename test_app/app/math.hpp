#ifndef TEST_APP_APP_MATH_H
#define TEST_APP_APP_MATH_H

#include "glm/glm.hpp"

// The conventions used are:
// +X is screen right
// +Y is screen up
// +Z is screen into

// - Radians for angles
// - +X axis is azimuth = 0, increasing clockwise
// - XZ plane is polar = 0, increasing towards +Y, decreasing towards -Y
// - Azimuth is in the interval [0, 2PI]
// - Zenith is in the interval [-PI/2, PI/2]

namespace test_app::app {

// X is azimuth, Y is pole, Z is radius
glm::vec3 cartesian_from_spherical(const glm::vec3 &);

float clamp(float, float min, float max);

float wrap(float, float min, float max);

}  // namespace test_app::app

#endif  // TEST_APP_APP_MATH_H
