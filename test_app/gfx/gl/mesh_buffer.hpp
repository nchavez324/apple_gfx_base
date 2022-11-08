#ifndef TEST_APP_GFX_GL_MESH_BUFFER_H
#define TEST_APP_GFX_GL_MESH_BUFFER_H

#include <optional>

#include "test_app/common/error_or.hpp"
#include "test_app/gfx/gl/bindings.h"
#include "test_app/gfx/mesh.hpp"

namespace test_app::gfx {

class MeshBuffer {
 public:
  static ErrorOr<MeshBuffer> Build(const Mesh &mesh);

  MeshBuffer(GLuint vertex_buffer, GLuint vertex_array, GLuint element_buffer,
             GLenum primitive_type, GLenum index_type, GLsizei index_count);
  MeshBuffer(const MeshBuffer &) = delete;
  MeshBuffer(MeshBuffer &&);
  MeshBuffer &operator=(const MeshBuffer &) = delete;
  MeshBuffer &operator=(MeshBuffer &&);
  ~MeshBuffer();

  GLuint vertex_buffer() const;
  GLuint vertex_array() const;
  GLuint element_buffer() const;
  GLenum primitive_type() const;
  GLenum index_type() const;
  GLsizei index_count() const;

 private:
  GLuint vertex_buffer_, vertex_array_, element_buffer_;
  GLenum primitive_type_;
  GLenum index_type_;
  GLsizei index_count_;

  static std::optional<GLenum> GLTypeFromVertexMemberType(
      VertexMemberType type);
  static std::optional<GLenum> GLTypeFromPrimitiveIndexSize(size_t index_size);
  static std::optional<GLenum> GLTypeFromPrimitiveType(PrimitiveType type);
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_GL_MESH_BUFFER_H
