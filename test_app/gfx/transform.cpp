#include "test_app/gfx/transform.hpp"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtx/string_cast.hpp"

namespace test_app::gfx {

Transform::Transform()
    : translation_(0.0f), rotation_(glm::vec3(0.0, 0.0, 0.0)), scale_(1.0f) {}

const glm::vec3 &Transform::translation() const { return translation_; }

const glm::quat &Transform::rotation() const { return rotation_; }

const glm::vec3 &Transform::scale() const { return scale_; }

glm::mat4 Transform::transform() const {
  glm::mat4 translation =
      glm::translate(glm::identity<glm::mat4>(), translation_);
  glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(),
                                   glm::angle(rotation_), glm::axis(rotation_));
  glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), scale_);
  return translation * rotation * scale;
}

void Transform::set_translation(glm::vec3 translation) {
  translation_ = translation;
}
void Transform::set_rotation(glm::quat rotation) { rotation_ = rotation; }

void Transform::set_scale(glm::vec3 scale) { scale_ = scale; }

}  // namespace test_app::gfx