#ifndef TEST_APP_GFX_TRANSFORM_H
#define TEST_APP_GFX_TRANSFORM_H

#include "glm/ext/quaternion_float.hpp"
#include "glm/vec3.hpp"

namespace test_app::gfx {
class Transform {
 public:
  Transform();
  Transform(const Transform &) = default;
  Transform(Transform &&) = default;
  Transform &operator=(const Transform &) = default;
  Transform &operator=(Transform &&) = default;
  ~Transform() = default;

  const glm::vec3 &translation() const;
  const glm::quat &rotation() const;
  const glm::vec3 &scale() const;
  glm::mat4 transform() const;

  void set_translation(glm::vec3);
  void set_rotation(glm::quat);
  void set_scale(glm::vec3);

 private:
  glm::vec3 translation_;
  glm::quat rotation_;
  glm::vec3 scale_;
};
}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_TRANSFORM_H
