#ifndef TEST_APP_GFX_GL_MATERIAL_BUFFER_H
#define TEST_APP_GFX_GL_MATERIAL_BUFFER_H

#include <optional>

#include "test_app/common/error_or.hpp"
#include "test_app/gfx/gl/bindings.h"
#include "test_app/gfx/material.hpp"
#include "test_app/gfx/shader.hpp"

namespace test_app::gfx {

class MaterialBuffer {
 public:
  static ErrorOr<MaterialBuffer> Build(const Material &material,
                                       const Shader &shader);
  MaterialBuffer(GLuint shader_program);
  MaterialBuffer(const MaterialBuffer &) = delete;
  MaterialBuffer(MaterialBuffer &&);
  MaterialBuffer &operator=(const MaterialBuffer &) = delete;
  MaterialBuffer &operator=(MaterialBuffer &&);
  ~MaterialBuffer();

  GLuint shader_program() const;

 private:
  GLuint shader_program_;

  static ErrorOr<std::string> ReadShaderSource(std::string source_path);
  static ErrorOr<GLuint> LoadShader(std::string source_path,
                                    GLenum shader_type);
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_GL_MATERIAL_BUFFER_H
