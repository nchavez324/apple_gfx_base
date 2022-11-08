#include "test_app/gfx/gl/material_buffer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace test_app::gfx {

ErrorOr<MaterialBuffer> MaterialBuffer::Build(const Material &material,
                                              const Shader &shader) {
  auto vertex_shader =
      LoadShader(shader.vertex_shader_path(), GL_VERTEX_SHADER);
  if (!vertex_shader.ok()) return vertex_shader.error();

  auto fragment_shader =
      LoadShader(shader.fragment_shader_path(), GL_FRAGMENT_SHADER);
  if (!fragment_shader.ok()) return fragment_shader.error();

  GLint success = 0;
  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, *vertex_shader);
  glAttachShader(shader_program, *fragment_shader);
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    return Error(ErrorCode::INVALID_ARGUMENT, std::string{info_log});
  }

  // TODO: Insufficient in case of earlier errors.
  glDeleteShader(*vertex_shader);
  glDeleteShader(*fragment_shader);
  return MaterialBuffer(shader_program);
}

MaterialBuffer::MaterialBuffer(GLuint shader_program)
    : shader_program_(shader_program) {}

MaterialBuffer::MaterialBuffer(MaterialBuffer &&from)
    : shader_program_{from.shader_program_} {
  from.shader_program_ = 0;
}

MaterialBuffer &MaterialBuffer::operator=(MaterialBuffer &&from) {
  this->shader_program_ = from.shader_program_;
  from.shader_program_ = 0;
  return *this;
}

MaterialBuffer::~MaterialBuffer() {
  if (shader_program_ != 0) glDeleteProgram(shader_program_);
}

GLuint MaterialBuffer::shader_program() const { return shader_program_; }

ErrorOr<std::string> MaterialBuffer::ReadShaderSource(std::string source_path) {
  std::ifstream ifs;
  ifs.open(source_path);
  if (!ifs.is_open()) {
    return Error(ErrorCode::NOT_FOUND, "Could not open shader source file");
  }

  std::ostringstream source_contents;
  source_contents << ifs.rdbuf();
  return source_contents.str();
}

ErrorOr<GLuint> MaterialBuffer::LoadShader(std::string source_path,
                                           GLenum shader_type) {
  auto source = ReadShaderSource(source_path);
  if (!source.ok()) return source.error();
  const char *source_cstr = source->c_str();

  GLint success = 0;
  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &source_cstr, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    return Error(ErrorCode::INVALID_ARGUMENT, std::string{info_log});
  }

  return shader;
}

}  // namespace test_app::gfx