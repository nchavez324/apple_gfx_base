#ifndef TEST_APP_INPUT_BUTTON_H
#define TEST_APP_INPUT_BUTTON_H

namespace test_app::input {
enum class Button : size_t {
  MOUSE_LEFT,
  MOUSE_RIGHT,
  MOUSE_MIDDLE,
  KEY_ARROW_UP,
  KEY_ARROW_DOWN,
  KEY_ARROW_LEFT,
  KEY_ARROW_RIGHT,
  KEY_UNKNOWN,
  COUNT,
};
}  // namespace test_app::input

#endif  // TEST_APP_INPUT_BUTTON_H
