#ifndef TEST_APP_INPUT_STATE_HPP
#define TEST_APP_INPUT_STATE_HPP

#include <array>

#include "glm/glm.hpp"
#include "test_app/input/button.hpp"

namespace test_app::input {

struct State {
  std::array<bool, (size_t)Button::COUNT> buttons;
  glm::ivec2 mouse_position;
};

}  // namespace test_app::input

#endif  // TEST_APP_INPUT_STATE_HPP
