#include "test_app/app/app.hpp"

#include <algorithm>
#include <cstdlib>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "test_app/app/math.hpp"
#include "test_app/app/mesh_builder.hpp"
#include "test_app/common/graphics_defines.h"
#include "test_app/common/time.hpp"
#include "test_app/gfx/camera.hpp"
#include "test_app/gfx/material.hpp"
#include "test_app/gfx/mesh_renderer.hpp"
#include "test_app/gfx/renderer.hpp"
#include "test_app/gfx/shader.hpp"
#include "test_app/gfx/transform.hpp"
#include "test_app/input/button_event.hpp"
#include "test_app/input/pointer_event.hpp"

namespace test_app::app {

static const float kCameraSpeed = 0.1f;

App::App(gfx::Surface surface, std::filesystem::path resource_path)
    : is_started_(false),
      is_stopping_(false),
      update_frame_(1),
      draw_frame_(0),
      draw_thread_(std::nullopt),
      resize_queue_(),
      draw_messages_(),
      draw_fence_(),
      scene_{},
      surface_{std::move(surface)},
      renderer_(resource_path),
      input_buffer_(),
      resource_path_(resource_path),
      camera_spherical_(glm::two_pi<float>() - glm::quarter_pi<float>(),
                        glm::quarter_pi<float>(), 5.0f),
      texture_material_{entt::null},
      color_material_{entt::null},
      triplane_mesh_{entt::null},
      triplane_{entt::null},
      axes_{entt::null},
      camera_{entt::null} {}

std::optional<Error> App::Prepare() {
  if (auto error = surface_.Prepare()) {
    return error.value();
  }
  if (auto error = renderer_.Prepare(scene_, surface_)) {
    return error.value();
  }

#if GFX_GL
  color_material_ = LoadMaterial("color.vert", "color.frag");
  texture_material_ = LoadMaterial("texture.vert", "texture.frag");

#elif GFX_METAL
  color_material_ = LoadMaterial("test_app::app::color::vertexShader",
                                 "test_app::app::color::fragmentShader");
  texture_material_ = LoadMaterial("test_app::app::texture::vertexShader",
                                   "test_app::app::texture::fragmentShader");
#endif

  entt::entity axes_mesh = scene_.registry().create();
  scene_.registry().emplace<gfx::Mesh>(axes_mesh, MeshBuilder::Axes());

  entt::entity cube_mesh = scene_.registry().create();
  scene_.registry().emplace<gfx::Mesh>(cube_mesh, MeshBuilder::Cube());

  triplane_mesh_ = scene_.registry().create();
  scene_.registry().emplace<gfx::Mesh>(triplane_mesh_, MeshBuilder::Triplane());

  axes_ = scene_.registry().create();
  scene_.registry().emplace<gfx::MeshRenderer>(axes_, axes_mesh,
                                               texture_material_);
  scene_.registry().emplace<gfx::Transform>(axes_);
  scene_.registry().patch<gfx::Transform>(axes_, [](auto &transform) {
    transform.set_translation(glm::vec3(0.0f, 0.0f, 0.0f));
  });

  for (int i = 0; i < 100; i++) {
    entt::entity cube = scene_.registry().create();
    scene_.registry().emplace<gfx::MeshRenderer>(cube, cube_mesh,
                                                 color_material_);
    scene_.registry().emplace<gfx::Transform>(cube);
    scene_.registry().patch<gfx::Transform>(cube, [](auto &transform) {
      transform.set_translation(
          glm::vec3(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50));
      glm::quat rotation_x = glm::angleAxis(
          (rand() % 360) * (glm::two_pi<float>() / 360.0f), glm::vec3(1, 0, 0));
      glm::quat rotation_y = glm::angleAxis(
          (rand() % 360) * (glm::two_pi<float>() / 360.0f), glm::vec3(0, 1, 0));
      glm::quat rotation_z = glm::angleAxis(
          (rand() % 360) * (glm::two_pi<float>() / 360.0f), glm::vec3(0, 0, 1));
      transform.set_rotation(rotation_x * rotation_y * rotation_z);
    });
  }

  triplane_ = scene_.registry().create();

  camera_ = scene_.registry().create();
  scene_.registry().emplace<gfx::Camera>(camera_,
                                         /* fov= */ glm::quarter_pi<float>(),
                                         /* near= */ 0.1f, /* far= */ 1000.0f);
  scene_.registry().emplace<gfx::Transform>(camera_);
  scene_.registry().patch<gfx::Transform>(camera_, [this](auto &transform) {
    glm::vec3 eye = cartesian_from_spherical(camera_spherical_);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    transform.set_translation(eye);
    transform.set_rotation(glm::quatLookAt(glm::normalize(target - eye), up));
  });

  draw_fence_.frame = 0;
  draw_thread_ = std::thread([this]() {
    while (!is_stopping_) {
      if (auto error = Draw()) {
        std::cout << error.value() << std::endl;
        return;
      }
    }
  });

  return std::nullopt;
}

std::optional<Error> App::Start() {
  is_started_ = true;
  return std::nullopt;
}

std::optional<Error> App::Update(uint64_t frame_time_current,
                                 uint64_t frame_time_next) {
  if (!is_started_) return std::nullopt;

  uint64_t before_update_time = system_time_nanos();
  if (before_update_time >= frame_time_next) {
    // std::cout << "App::Update: Dropping frame, behind: "
    //           << (before_update_time - frame_time_next) << std::endl;
    return std::nullopt;
  }
  // std::cout << "App::Update(" << update_frame_ << ") begin, "
  //           << "left: " << (frame_time_next - before_update_time) <<
  //           std::endl;
  int frames_per_second =
      static_cast<int>(1000000000.0 / (frame_time_next - frame_time_current));

  std::unique_lock draw_fence_lock(draw_fence_.mutex);
  if (draw_fence_.frame > 0 && update_frame_ >= 2 &&
      draw_fence_.frame < update_frame_ - 2) {
    // std::cout << "App::Update: Waiting for draw fence" << std::endl;
    draw_fence_.condition.wait(draw_fence_lock, [this] {
      return draw_fence_.frame >= update_frame_ - 2;
    });
  }
  draw_fence_lock.unlock();

  std::optional<glm::uvec2> new_size = std::nullopt;
  if (resize_queue_.new_size) {
    new_size = resize_queue_.new_size;
    resize_queue_.new_size = std::nullopt;
  }
  if (new_size && *new_size != surface_.viewport_size()) {
    // std::cout << "App::Update: Resizing to: " << new_size->x << ", "
    //           << new_size->y << std::endl;
    std::unique_lock surface_lock(resize_queue_.mutex);
    surface_.Resize(*new_size);
    resize_queue_.condition.notify_one();
    surface_lock.unlock();
  }

  input_buffer_.FlushToCurrent();

  if (update_frame_ == 60) {
    scene_.registry().emplace<gfx::MeshRenderer>(triplane_, triplane_mesh_,
                                                 texture_material_);
    scene_.registry().emplace<gfx::Transform>(triplane_);
  }
  if (update_frame_ == 90) {
    scene_.registry().patch<gfx::MeshRenderer>(
        triplane_, [this](auto &mesh_renderer) {
          mesh_renderer.set_material(color_material_);
        });
  }
  if (update_frame_ == 120) {
    scene_.registry().patch<gfx::Transform>(triplane_, [](auto &transform) {
      transform.set_translation(glm::vec3(-0.5f, -0.5f, -0.5f));
    });
  }
  if (update_frame_ == 150) {
    scene_.registry().remove<gfx::Transform>(triplane_);
    scene_.registry().remove<gfx::MeshRenderer>(triplane_);
  }

  if (update_frame_ == 180) {
    scene_.registry().patch<gfx::MeshRenderer>(
        axes_, [this](auto &mesh_renderer) {
          mesh_renderer.set_material(color_material_);
        });
  }

  if (input_buffer_.IsDown(input::Button::MOUSE_LEFT)) {
    camera_spherical_.z += kCameraSpeed;
  }
  if (input_buffer_.IsDown(input::Button::MOUSE_RIGHT)) {
    camera_spherical_.z = std::max(0.0f, camera_spherical_.z - kCameraSpeed);
  }
  if (input_buffer_.IsDown(input::Button::KEY_ARROW_LEFT)) {
    camera_spherical_.x =
        wrap(camera_spherical_.x - kCameraSpeed, 0, glm::two_pi<float>());
  }
  if (input_buffer_.IsDown(input::Button::KEY_ARROW_RIGHT)) {
    camera_spherical_.x =
        wrap(camera_spherical_.x + kCameraSpeed, 0, glm::two_pi<float>());
  }
  if (input_buffer_.IsDown(input::Button::KEY_ARROW_UP)) {
    camera_spherical_.y = clamp(camera_spherical_.y + kCameraSpeed,
                                -glm::half_pi<float>(), +glm::half_pi<float>());
  }
  if (input_buffer_.IsDown(input::Button::KEY_ARROW_DOWN)) {
    camera_spherical_.y = clamp(camera_spherical_.y - kCameraSpeed,
                                -glm::half_pi<float>(), +glm::half_pi<float>());
  }

  scene_.registry().patch<gfx::Transform>(camera_, [this](auto &transform) {
    glm::vec3 eye = cartesian_from_spherical(camera_spherical_);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    transform.set_translation(eye);
    transform.set_rotation(glm::quatLookAt(glm::normalize(target - eye), up));
  });

  DrawMessage draw_message = {
      .is_stopping = false,
      .frame = update_frame_,
      .frame_time_current = frame_time_current,
      .frame_time_next = frame_time_next,
  };
  std::unique_lock draw_messages_lock(draw_messages_.mutex);
  draw_messages_.queue.push(draw_message);
  draw_messages_lock.unlock();
  draw_messages_.condition.notify_one();

  uint64_t after_update_time = system_time_nanos();
  // std::cout << "App::Update(" << update_frame_
  //           << ") end, left: " << (frame_time_next - after_update_time) << ",
  //           "
  //           << frames_per_second << " fps" << std::endl;
  update_frame_++;

  return std::nullopt;
}

std::optional<Error> App::Draw() {
  std::queue<DrawMessage> pending_queue;
  std::unique_lock draw_messages_lock(draw_messages_.mutex);
  if (draw_messages_.queue.empty()) {
    // std::cout << "App::Draw: Waiting on update" << std::endl;
    draw_messages_.condition.wait(
        draw_messages_lock, [this] { return !draw_messages_.queue.empty(); });
  }
  while (!draw_messages_.queue.empty()) {
    pending_queue.push(draw_messages_.queue.front());
    draw_messages_.queue.pop();
  }
  draw_messages_lock.unlock();

  while (pending_queue.size() > 1) {
    const DrawMessage &message = pending_queue.front();
    if (message.is_stopping) {
      return std::nullopt;
    }
    // std::cout << "App::Draw: Dropping frame " << message.frame << std::endl;
    pending_queue.pop();
  }
  DrawMessage draw_message = std::move(pending_queue.front());
  pending_queue.pop();
  draw_frame_ = draw_message.frame;

  uint64_t before_draw_time = system_time_nanos();
  // std::cout << "App::Draw(" << draw_frame_ << ") begin, left: "
  //           << (draw_message.frame_time_next - before_draw_time) <<
  //           std::endl;

  // Lock access to the surface, so it isn't resized during a draw.
  std::unique_lock surface_lock(resize_queue_.mutex);
  if (auto error = renderer_.Draw(scene_, surface_)) {
    return error.value();
  }
  resize_queue_.condition.notify_one();
  surface_lock.unlock();
  uint64_t after_draw_time = system_time_nanos();
  // std::cout << "App::Draw(" << draw_frame_ << ") end, left: "
  //           << (draw_message.frame_time_next - after_draw_time) << std::endl;

  std::unique_lock draw_fence_lock(draw_fence_.mutex);
  draw_fence_.frame = draw_frame_;
  draw_fence_lock.unlock();
  draw_fence_.condition.notify_one();

  return std::nullopt;
}

void App::Resize(glm::uvec2 new_size) { resize_queue_.new_size = new_size; }

void App::EnqueueInput(std::unique_ptr<input::Event> input_event) {
  input_buffer_.Enqueue(std::move(input_event));
}

std::optional<Error> App::Stop() {
  is_stopping_ = true;
  if (draw_thread_) {
    DrawMessage draw_message = {
        .is_stopping = true,
    };
    std::unique_lock draw_messages_lock(draw_messages_.mutex);
    draw_messages_.queue.push(draw_message);
    draw_messages_lock.unlock();
    draw_messages_.condition.notify_one();

    draw_thread_->join();
    draw_thread_ = std::nullopt;
  }

  if (auto error = renderer_.Stop(scene_)) {
    return error.value();
  }

  return std::nullopt;
}

#if GFX_GL
entt::entity App::LoadMaterial(std::string vertex_key,
                               std::string fragment_key) {
  entt::entity shader = scene_.registry().create();
  scene_.registry().emplace<gfx::Shader>(shader, resource_path_ / vertex_key,
                                         resource_path_ / fragment_key);
  entt::entity material = scene_.registry().create();
  scene_.registry().emplace<gfx::Material>(material, shader);
  return material;
}

#elif GFX_METAL
entt::entity App::LoadMaterial(std::string vertex_key,
                               std::string fragment_key) {
  std::filesystem::path shader_library_path = resource_path_ / "metal.metallib";
  entt::entity shader = scene_.registry().create();
  scene_.registry().emplace<gfx::Shader>(shader, shader_library_path,
                                         vertex_key, fragment_key);
  entt::entity material = scene_.registry().create();
  scene_.registry().emplace<gfx::Material>(material, shader);
  return material;
}
#endif

}  // namespace test_app::app
