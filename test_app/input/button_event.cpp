#include "test_app/input/button_event.hpp"

namespace test_app::input {

ButtonEvent::ButtonEvent(std::chrono::system_clock::time_point time,
                         ButtonEventType type, Button button)
    : Event(time), type_(type), button_(button) {}

ButtonEventType ButtonEvent::type() const { return type_; }

Button ButtonEvent::button() const { return button_; }

}  // namespace test_app::input
