#ifndef TEST_APP_INPUT_POINTER_EVENT_HPP
#define TEST_APP_INPUT_POINTER_EVENT_HPP

#include <chrono>

#include "glm/glm.hpp"
#include "test_app/input/event.hpp"

namespace test_app::input {

class PointerEvent : public Event {
 public:
  PointerEvent(std::chrono::system_clock::time_point time, glm::ivec2 position);

  glm::ivec2 position() const;

 private:
  glm::ivec2 position_;
};

}  // namespace test_app::input

#endif  // TEST_APP_INPUT_POINTER_EVENT_HPP
