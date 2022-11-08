#ifndef TEST_APP_INPUT_BUTTON_EVENT_HPP
#define TEST_APP_INPUT_BUTTON_EVENT_HPP

#include <chrono>

#include "test_app/input/button.hpp"
#include "test_app/input/event.hpp"

namespace test_app::input {

enum class ButtonEventType {
  DOWN,
  UP,
};

class ButtonEvent : public Event {
 public:
  ButtonEvent(std::chrono::system_clock::time_point time, ButtonEventType type,
              Button button);

  ButtonEventType type() const;
  Button button() const;

 private:
  ButtonEventType type_;
  Button button_;
};

}  // namespace test_app::input

#endif  // TEST_APP_INPUT_BUTTON_EVENT_HPP
