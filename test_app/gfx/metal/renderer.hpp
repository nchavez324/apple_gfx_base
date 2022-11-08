#ifndef TEST_APP_GFX_METAL_RENDERER_H
#define TEST_APP_GFX_METAL_RENDERER_H

#include <filesystem>
#include <memory>
#include <optional>

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "test_app/common/error.hpp"
#include "test_app/gfx/mesh.hpp"
#include "test_app/gfx/metal/uniform_types.hpp"
#include "test_app/gfx/scene.hpp"
#include "test_app/gfx/surface.hpp"
#include "test_app/gfx/transform.hpp"
#include "third_party/apple_cpp/Metal/Metal.hpp"

namespace test_app::gfx {
class Renderer {
 public:
  Renderer(std::filesystem::path resource_path);
  Renderer(const Renderer &) = delete;
  Renderer(Renderer &&);
  Renderer &operator=(const Renderer &) = delete;
  Renderer &operator=(Renderer &&) = delete;
  ~Renderer();

  /**
   * The surface will start issuing draw requests after this. This is called on
   * the main thread.
   */
  std::optional<Error> Prepare(Scene &scene, Surface &Surface);
  /** The surface is requesting a draw. This is called on the draw thread. */
  std::optional<Error> Draw(Scene &scene, Surface &surface);
  std::optional<Error> Stop(Scene &scene);

 private:
  entt::observer mesh_observer_, material_observer_;
  std::filesystem::path resource_path_;
  MTL::CommandQueue *command_queue_;
  MTL::Texture *texture_;

  std::optional<Error> UploadMeshes(Scene &scene, Surface &surface);
  std::optional<Error> UploadMaterials(Scene &scene, Surface &surface);

  Uniforms GenerateUniforms(const Transform &transform);
  static std::optional<Error> LoadTexture(
      const std::filesystem::path &resource_path, MTL::Device *device,
      MTL::Texture *&texture);
};
}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_METAL_RENDERER_H
