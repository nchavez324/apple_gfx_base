#include "test_app/gfx/gl/shader.hpp"

namespace test_app::gfx {

Shader::Shader(std::filesystem::path vertex_shader_path,
               std::filesystem::path fragment_shader_path)
    : vertex_shader_path_{std::move(vertex_shader_path)},
      fragment_shader_path_{std::move(fragment_shader_path)} {}

const std::filesystem::path &Shader::vertex_shader_path() const {
  return vertex_shader_path_;
}
const std::filesystem::path &Shader::fragment_shader_path() const {
  return fragment_shader_path_;
}

}  // namespace test_app::gfx
