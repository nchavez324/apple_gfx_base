#ifndef TEST_APP_GFX_METAL_SHADER
#define TEST_APP_GFX_METAL_SHADER

#include <filesystem>

namespace test_app::gfx {

class Shader {
 public:
  Shader(std::filesystem::path library_path, std::string vertex_function_name,
         std::string fragment_function_name);
  Shader(const Shader &) = delete;
  Shader(Shader &&) = default;
  Shader &operator=(const Shader &) = delete;
  Shader &operator=(Shader &&) = default;
  ~Shader() = default;

  const std::filesystem::path &library_path() const;
  const std::string &vertex_function_name() const;
  const std::string &fragment_function_name() const;

 protected:
  std::filesystem::path library_path_;
  std::string vertex_function_name_;
  std::string fragment_function_name_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_METAL_SHADER
