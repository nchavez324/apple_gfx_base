#ifndef TEST_APP_COMMON_SEMAPHORE_H
#define TEST_APP_COMMON_SEMAPHORE_H

#include <condition_variable>
#include <mutex>

namespace test_app {

class Semaphore {
 public:
  Semaphore();

  void Notify();
  void Wait();

 private:
  std::mutex mutex_;
  std::condition_variable condition_;
  int count_;
};

}  // namespace test_app

#endif  // TEST_APP_COMMON_SEMAPHORE_H
