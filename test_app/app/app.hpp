#ifndef TEST_APP_APP_APP_H
#define TEST_APP_APP_APP_H

#include <chrono>
#include <filesystem>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "test_app/common/error.hpp"
#include "test_app/common/semaphore.hpp"
#include "test_app/gfx/renderer.hpp"
#include "test_app/gfx/scene.hpp"
#include "test_app/gfx/surface.hpp"
#include "test_app/input/buffer.hpp"
#include "test_app/input/event.hpp"

namespace test_app::app {

struct DrawMessage {
  bool is_stopping;
  uint64_t frame;
  uint64_t frame_time_current;
  uint64_t frame_time_next;
};

struct DrawMessages {
  std::queue<DrawMessage> queue;
  std::mutex mutex;
  std::condition_variable condition;
};

struct DrawFence {
  uint64_t frame;
  std::mutex mutex;
  std::condition_variable condition;
};

struct ResizeQueue {
  // TODO: Merge with input into single "platform" events queue.
  std::optional<glm::uvec2> new_size;
  std::mutex mutex;
  std::condition_variable condition;
};

class App {
 public:
  App(gfx::Surface surface, std::filesystem::path resource_path);
  App(const App &) = delete;
  App(App &&) = delete;
  App &operator=(const App &) = delete;
  App &operator=(App &&) = delete;
  ~App() = default;

  std::optional<Error> Prepare();
  std::optional<Error> Start();
  std::optional<Error> Update(uint64_t frame_time_current,
                              uint64_t frame_time_next);
  std::optional<Error> Draw();
  std::optional<Error> Stop();

  // TODO: As other OS/UI events become relevant, these all should be lumped up
  // somehow, instead of a method for each.
  void Resize(glm::uvec2 new_size);
  void EnqueueInput(std::unique_ptr<input::Event> input_event);

 private:
  bool is_started_, is_stopping_;
  unsigned int update_frame_, draw_frame_;
  std::optional<std::thread> draw_thread_;

  ResizeQueue resize_queue_;
  DrawMessages draw_messages_;
  DrawFence draw_fence_;

  gfx::Scene scene_;
  gfx::Surface surface_;
  gfx::Renderer renderer_;
  input::Buffer input_buffer_;
  std::filesystem::path resource_path_;

  glm::vec3 camera_spherical_;
  entt::entity texture_material_, color_material_, triplane_mesh_, triplane_,
      axes_, camera_;

  entt::entity LoadMaterial(std::string vertex_key, std::string fragment_key);
};

}  // namespace test_app::app

#endif  // TEST_APP_APP_APP_H
