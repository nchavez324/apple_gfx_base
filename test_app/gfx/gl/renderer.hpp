#ifndef TEST_APP_GFX_GL_RENDERER_H
#define TEST_APP_GFX_GL_RENDERER_H

#include <filesystem>
#include <memory>
#include <optional>
#include <variant>

#include "entt/entt.hpp"
#include "glm/glm.hpp"
#include "test_app/common/error.hpp"
#include "test_app/common/error_or.hpp"
#include "test_app/common/graphics_defines.h"
#include "test_app/gfx/gl/bindings.h"
#include "test_app/gfx/mesh.hpp"
#include "test_app/gfx/primitive_type.hpp"
#include "test_app/gfx/scene.hpp"
#include "test_app/gfx/surface.hpp"

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
  std::optional<Error> Prepare(Scene &scene, Surface &surface);
  /** The surface is requesting a draw. This is called on the draw thread. */
  std::optional<Error> Draw(Scene &scene, Surface &surface);
  std::optional<Error> Stop(Scene &scene);

 private:
  entt::observer mesh_observer_, material_observer_;
  std::filesystem::path resource_path_;
  GLuint texture_;

  std::optional<Error> UploadMeshes(Scene &scene);
  std::optional<Error> UploadMaterials(Scene &scene);

  void MakeCurrentContext();
  static ErrorOr<GLuint> LoadTexture(
      const std::filesystem::path &resource_path);
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_GL_RENDERER_H
