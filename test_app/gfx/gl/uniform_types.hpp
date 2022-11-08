#ifndef TEST_APP_GFX_GL_UNIFORM_TYPES_H
#define TEST_APP_GFX_GL_UNIFORM_TYPES_H

#include <glm/glm.hpp>

namespace test_app {
namespace gfx {

enum class VertexFunctionArgument {
  VERTICES = 0,
  UNIFORMS = 1,
};

struct Uniforms {
  float scale;
  glm::uvec2 viewport_size;
};

}  // namespace gfx
}  // namespace test_app

#endif  // TEST_APP_GFX_GL_UNIFORM_TYPES_H
