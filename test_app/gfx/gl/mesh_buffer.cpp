#include "test_app/gfx/gl/mesh_buffer.hpp"

#include "test_app/common/graphics_defines.h"

namespace test_app::gfx {

ErrorOr<MeshBuffer> MeshBuffer::Build(const Mesh &mesh) {
  GLuint vertex_buffer = 0, vertex_array = 0, element_buffer = 0;
  glGenVertexArrays(1, &vertex_array);
  glGenBuffers(1, &vertex_buffer);
  glGenBuffers(1, &element_buffer);

  glBindVertexArray(vertex_array);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(mesh.vertex_buffer_size()),
               mesh.vertex_buffer(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               static_cast<GLsizeiptr>(mesh.primitive().index_buffer_size()),
               mesh.primitive().index_buffer(), GL_STATIC_DRAW);

  GLsizei stride = static_cast<GLsizei>(mesh.vertex_descriptor().size());
  for (size_t member_index = 0;
       member_index < mesh.vertex_descriptor().members().size();
       member_index++) {
    const VertexMember &vertex_member =
        mesh.vertex_descriptor().members()[member_index];
    GLsizei member_size = static_cast<GLsizei>(vertex_member.size);
    GLsizei member_offset = static_cast<GLsizei>(vertex_member.offset);
    auto member_gl_type = GLTypeFromVertexMemberType(vertex_member.type);
    if (!member_gl_type) {
      return Error(ErrorCode::INVALID_ARGUMENT, "Invalid vertex member type");
    }

    glVertexAttribPointer(
        /* index= */ member_index,
        /* size= */ member_size,
        /* type= */ *member_gl_type,
        /* normalized= */ GL_FALSE,
        /* stride= */ stride,
        /* offset= */ reinterpret_cast<GLvoid *>(member_offset));
    glEnableVertexAttribArray(member_index);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  auto index_type = GLTypeFromPrimitiveIndexSize(mesh.primitive().index_size());
  if (!index_type) {
    return Error(ErrorCode::INVALID_ARGUMENT, "Invalid primitive index size");
  }

  auto primitive_type = GLTypeFromPrimitiveType(mesh.primitive().type());
  if (!primitive_type) {
    return Error(ErrorCode::INVALID_ARGUMENT, "Invalid primitive type");
  }

  return MeshBuffer(vertex_buffer, vertex_array, element_buffer,
                    *primitive_type, *index_type,
                    mesh.primitive().index_count());
}

MeshBuffer::MeshBuffer(GLuint vertex_buffer, GLuint vertex_array,
                       GLuint element_buffer, GLenum primitive_type,
                       GLenum index_type, GLsizei index_count)
    : vertex_buffer_(vertex_buffer),
      vertex_array_(vertex_array),
      element_buffer_(element_buffer),
      primitive_type_(primitive_type),
      index_type_(index_type),
      index_count_(index_count) {}

MeshBuffer::MeshBuffer(MeshBuffer &&from)
    : vertex_buffer_(from.vertex_buffer_),
      vertex_array_(from.vertex_array_),
      element_buffer_(from.element_buffer_),
      primitive_type_(from.primitive_type_),
      index_type_(from.index_type_),
      index_count_(from.index_count_) {
  from.vertex_buffer_ = 0;
  from.vertex_array_ = 0;
  from.element_buffer_ = 0;
  from.index_count_ = 0;
}

MeshBuffer &MeshBuffer::operator=(MeshBuffer &&from) {
  this->vertex_buffer_ = from.vertex_buffer_;
  from.vertex_buffer_ = 0;
  this->vertex_array_ = from.vertex_array_;
  from.vertex_array_ = 0;
  this->element_buffer_ = from.element_buffer_;
  from.element_buffer_ = 0;
  this->primitive_type_ = from.primitive_type_;
  this->index_type_ = from.index_type_;
  this->index_count_ = from.index_count_;
  from.index_count_ = 0;
  return *this;
}

MeshBuffer::~MeshBuffer() {
  if (element_buffer_ != 0) glDeleteBuffers(1, &element_buffer_);
  if (vertex_array_ != 0) glDeleteVertexArrays(1, &vertex_array_);
  if (vertex_buffer_ != 0) glDeleteBuffers(1, &vertex_buffer_);
}

GLuint MeshBuffer::vertex_buffer() const { return vertex_buffer_; }
GLuint MeshBuffer::vertex_array() const { return vertex_array_; }
GLuint MeshBuffer::element_buffer() const { return element_buffer_; }
GLenum MeshBuffer::primitive_type() const { return primitive_type_; }
GLenum MeshBuffer::index_type() const { return index_type_; }
GLsizei MeshBuffer::index_count() const { return index_count_; }

std::optional<GLenum> MeshBuffer::GLTypeFromVertexMemberType(
    VertexMemberType type) {
  switch (type) {
    case VertexMemberType::BYTE:
      return GL_BYTE;
    case VertexMemberType::UBYTE:
      return GL_UNSIGNED_BYTE;
    case VertexMemberType::SHORT:
      return GL_SHORT;
    case VertexMemberType::USHORT:
      return GL_UNSIGNED_SHORT;
    case VertexMemberType::INT:
      return GL_INT;
    case VertexMemberType::UINT:
      return GL_UNSIGNED_INT;
    case VertexMemberType::HALF_FLOAT:
      return GL_HALF_FLOAT;
    case VertexMemberType::FLOAT:
      return GL_FLOAT;
#if !GFX_OPEN_GLES
    case VertexMemberType::DOUBLE:
      return GL_DOUBLE;
#endif
    default:
      return std::nullopt;
  }
}

std::optional<GLenum> MeshBuffer::GLTypeFromPrimitiveIndexSize(
    size_t index_size) {
  switch (index_size) {
    case sizeof(uint8_t):
      return GL_UNSIGNED_BYTE;
    case sizeof(uint16_t):
      return GL_UNSIGNED_SHORT;
    case sizeof(uint32_t):
      return GL_UNSIGNED_INT;
    default:
      return std::nullopt;
  }
}

std::optional<GLenum> MeshBuffer::GLTypeFromPrimitiveType(PrimitiveType type) {
  switch (type) {
    case PrimitiveType::POINT:
      return GL_POINTS;
    case PrimitiveType::LINE:
      return GL_LINES;
    case PrimitiveType::LINE_STRIP:
      return GL_LINE_STRIP;
    case PrimitiveType::TRIANGLE:
      return GL_TRIANGLES;
    case PrimitiveType::TRIANGLE_STRIP:
      return GL_TRIANGLE_STRIP;
    default:
      return std::nullopt;
  }
}

}  // namespace test_app::gfx
