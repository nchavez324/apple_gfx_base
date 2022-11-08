#include "test_app/input/pointer_event.hpp"

namespace test_app::input {

PointerEvent::PointerEvent(std::chrono::system_clock::time_point time,
                           glm::ivec2 position)
    : Event(time), position_(position) {}

glm::ivec2 PointerEvent::position() const { return position_; }

}  // namespace test_app::input
