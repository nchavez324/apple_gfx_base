#include "test_app/gfx/mesh.hpp"

namespace test_app::gfx {

Mesh::Mesh(Primitive primitive, VertexDescriptor vertex_descriptor,
           size_t vertex_count, const void *vertex_buffer)
    : primitive_{std::move(primitive)},
      vertex_descriptor_{std::move(vertex_descriptor)},
      vertex_count_{vertex_count},
      vertex_buffer_{malloc(vertex_count * vertex_descriptor.size())} {
  memcpy(vertex_buffer_, vertex_buffer,
         vertex_count * vertex_descriptor.size());
}

Mesh::Mesh(Mesh &&from)
    : primitive_{std::move(from.primitive_)},
      vertex_descriptor_{std::move(from.vertex_descriptor_)},
      vertex_count_{from.vertex_count_},
      vertex_buffer_{from.vertex_buffer_} {
  from.vertex_count_ = 0;
  from.vertex_buffer_ = nullptr;
}

Mesh &Mesh::operator=(Mesh &&from) {
  this->primitive_ = std::move(from.primitive_);
  this->vertex_descriptor_ = std::move(from.vertex_descriptor_);
  this->vertex_count_ = from.vertex_count_;
  from.vertex_count_ = 0;
  this->vertex_buffer_ = from.vertex_buffer_;
  from.vertex_buffer_ = nullptr;
  return *this;
}

Mesh::~Mesh() {
  if (vertex_buffer_ != nullptr) free(vertex_buffer_);
}

const Primitive &Mesh::primitive() const { return primitive_; }
const VertexDescriptor &Mesh::vertex_descriptor() const {
  return vertex_descriptor_;
}
size_t Mesh::vertex_count() const { return vertex_count_; }
const void *Mesh::vertex_buffer() const { return vertex_buffer_; }
size_t Mesh::vertex_buffer_size() const {
  return vertex_count_ * vertex_descriptor_.size();
}

}  // namespace test_app::gfx