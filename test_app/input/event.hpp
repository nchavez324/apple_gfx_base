#ifndef TEST_APP_INPUT_EVENT_HPP
#define TEST_APP_INPUT_EVENT_HPP

#include <chrono>

namespace test_app::input {

class Event {
 public:
  Event(std::chrono::system_clock::time_point time);
  virtual ~Event() = default;

  std::chrono::system_clock::time_point time() const;

 private:
  std::chrono::system_clock::time_point time_;
};

}  // namespace test_app::input

#endif  // TEST_APP_INPUT_EVENT_HPP
