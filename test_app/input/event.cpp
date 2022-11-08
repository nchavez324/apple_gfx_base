#include "test_app/input/event.hpp"

namespace test_app::input {

Event::Event(std::chrono::system_clock::time_point time) : time_(time) {}

std::chrono::system_clock::time_point Event::time() const { return time_; }

}  // namespace test_app::input
