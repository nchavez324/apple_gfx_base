#include "test_app/gfx/metal/shader.hpp"

namespace test_app::gfx {

Shader::Shader(std::filesystem::path library_path,
               std::string vertex_function_name,
               std::string fragment_function_name)
    : library_path_{std::move(library_path)},
      vertex_function_name_{std::move(vertex_function_name)},
      fragment_function_name_{std::move(fragment_function_name)} {}

const std::filesystem::path &Shader::library_path() const {
  return library_path_;
}
const std::string &Shader::vertex_function_name() const {
  return vertex_function_name_;
}
const std::string &Shader::fragment_function_name() const {
  return fragment_function_name_;
}

}  // namespace test_app::gfx