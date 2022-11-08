#include "test_app/common/semaphore.hpp"

namespace test_app {

Semaphore::Semaphore() : mutex_{}, condition_{}, count_{0} {}

void Semaphore::Notify() {
  std::unique_lock lock{mutex_};
  count_++;
  condition_.notify_one();
}

void Semaphore::Wait() {
  std::unique_lock lock{mutex_};
  condition_.wait(lock, [this] { return count_ > 0; });
  count_--;
}

}  // namespace test_app
