#include "test_app/input/buffer.hpp"

#include "test_app/input/button_event.hpp"
#include "test_app/input/pointer_event.hpp"

namespace test_app::input {

Buffer::Buffer() : queue_(), current_state_(), previous_state_() {
  for (size_t i = 0; i < (size_t)Button::COUNT; i++) {
    current_state_.buttons[i] = false;
    previous_state_.buttons[i] = false;
  }
  current_state_.mouse_position = glm::ivec2(0, 0);
  previous_state_.mouse_position = glm::ivec2(0, 0);
}

void Buffer::Enqueue(std::unique_ptr<Event> event) {
  queue_.push(std::move(event));
}

void Buffer::FlushToCurrent() {
  previous_state_ = current_state_;

  while (!queue_.empty()) {
    std::unique_ptr<Event> event = std::move(queue_.front());
    queue_.pop();
    auto button_event = dynamic_cast<ButtonEvent *>(event.get());
    if (button_event != nullptr) {
      bool isDown = button_event->type() == ButtonEventType::DOWN;
      current_state_.buttons[(size_t)button_event->button()] = isDown;
      continue;
    }
    auto pointer_event = dynamic_cast<PointerEvent *>(event.get());
    if (pointer_event != nullptr) {
      current_state_.mouse_position = pointer_event->position();
      continue;
    }
  }
}

bool Buffer::DidPress(Button button) {
  return current_state_.buttons[(size_t)button] &&
         !previous_state_.buttons[(size_t)button];
}

bool Buffer::IsDown(Button button) {
  return current_state_.buttons[(size_t)button];
}

const State &Buffer::current_state() const { return current_state_; }
const State &Buffer::previous_state() const { return previous_state_; }

}  // namespace test_app::input