#ifndef TEST_APP_INPUT_BUFFER_HPP
#define TEST_APP_INPUT_BUFFER_HPP

#include <memory>
#include <queue>

#include "test_app/input/event.hpp"
#include "test_app/input/state.hpp"

namespace test_app::input {

class Buffer {
 public:
  Buffer();

  void Enqueue(std::unique_ptr<Event> event);
  void FlushToCurrent();

  bool DidPress(Button);
  bool IsDown(Button);

  const State &current_state() const;
  const State &previous_state() const;

 private:
  std::queue<std::unique_ptr<Event>> queue_;
  State current_state_, previous_state_;
};

}  // namespace test_app::input

#endif  // TEST_APP_INPUT_BUFFER_HPP
