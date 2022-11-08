#ifndef TEST_APP_GFX_GL_SHADER
#define TEST_APP_GFX_GL_SHADER

#include <filesystem>

namespace test_app::gfx {

class Shader {
 public:
  Shader(std::filesystem::path vertex_shader_path,
         std::filesystem::path fragment_shader_path);
  Shader(const Shader &) = delete;
  Shader(Shader &&) = default;
  Shader &operator=(const Shader &) = delete;
  Shader &operator=(Shader &&) = default;
  ~Shader() = default;

  const std::filesystem::path &vertex_shader_path() const;
  const std::filesystem::path &fragment_shader_path() const;

 protected:
  std::filesystem::path vertex_shader_path_;
  std::filesystem::path fragment_shader_path_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_GL_SHADER
