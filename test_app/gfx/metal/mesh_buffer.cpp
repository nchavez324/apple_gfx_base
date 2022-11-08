#include "test_app/gfx/metal/mesh_buffer.hpp"

namespace test_app::gfx {

ErrorOr<MeshBuffer> MeshBuffer::Build(MTL::Device *device, const Mesh &mesh) {
  MTL::Buffer *vertex_buffer =
      device
          ->newBuffer(mesh.vertex_buffer(), mesh.vertex_buffer_size(),
                      MTL::ResourceStorageModeShared)
          ->autorelease();
  vertex_buffer->setLabel(NS::String::alloc()
                              ->init("Vertices", NS::ASCIIStringEncoding)
                              ->autorelease());
  MTL::Buffer *index_buffer =
      device
          ->newBuffer(mesh.primitive().index_buffer(),
                      mesh.primitive().index_buffer_size(),
                      MTL::ResourceStorageModeShared)
          ->autorelease();
  index_buffer->setLabel(NS::String::alloc()
                             ->init("Indices", NS::ASCIIStringEncoding)
                             ->autorelease());
  auto index_type = MTLIndexTypeFromIndexSize(mesh.primitive().index_size());
  if (!index_type) {
    return Error(ErrorCode::INVALID_ARGUMENT,
                 "Unrecognized index size. Must be 16 or 32 bits.");
  }
  return MeshBuffer(vertex_buffer, index_buffer,
                    MTLPrimitiveTypeFromPrimitiveType(mesh.primitive().type()),
                    index_type.value(), mesh.primitive().index_count());
}

MeshBuffer::MeshBuffer(MTL::Buffer *vertex_buffer, MTL::Buffer *index_buffer,
                       MTL::PrimitiveType primitive_type,
                       MTL::IndexType index_type, size_t index_count)
    : vertex_buffer_{vertex_buffer->retain()},
      index_buffer_{index_buffer->retain()},
      primitive_type_{primitive_type},
      index_type_{index_type},
      index_count_{index_count} {}

MeshBuffer::MeshBuffer(MeshBuffer &&from)
    : vertex_buffer_{from.vertex_buffer_},
      index_buffer_{from.index_buffer_},
      primitive_type_{from.primitive_type_},
      index_type_{from.index_type_},
      index_count_{from.index_count_} {
  from.vertex_buffer_ = nullptr;
  from.index_buffer_ = nullptr;
  from.index_count_ = 0;
}

MeshBuffer &MeshBuffer::operator=(MeshBuffer &&from) {
  this->vertex_buffer_ = from.vertex_buffer_;
  from.vertex_buffer_ = nullptr;
  this->index_buffer_ = from.index_buffer_;
  from.index_buffer_ = nullptr;
  this->index_type_ = from.index_type_;
  this->primitive_type_ = from.primitive_type_;
  this->index_count_ = from.index_count_;
  from.index_count_ = 0;
  return *this;
}

MeshBuffer::~MeshBuffer() {
  index_buffer_->release();
  vertex_buffer_->release();
}

MTL::Buffer *MeshBuffer::vertex_buffer() { return vertex_buffer_; }
MTL::Buffer *MeshBuffer::index_buffer() { return index_buffer_; }
MTL::PrimitiveType MeshBuffer::primitive_type() const {
  return primitive_type_;
}
MTL::IndexType MeshBuffer::index_type() const { return index_type_; }
size_t MeshBuffer::index_count() const { return index_count_; }

std::optional<MTL::IndexType> MeshBuffer::MTLIndexTypeFromIndexSize(
    size_t index_size) {
  switch (index_size) {
    case sizeof(uint16_t):
      return MTL::IndexTypeUInt16;
    case sizeof(uint32_t):
      return MTL::IndexTypeUInt32;
    default:
      return std::nullopt;
  }
}

MTL::PrimitiveType MeshBuffer::MTLPrimitiveTypeFromPrimitiveType(
    gfx::PrimitiveType primitive_type) {
  switch (primitive_type) {
    case PrimitiveType::POINT:
      return MTL::PrimitiveTypePoint;
    case PrimitiveType::LINE:
      return MTL::PrimitiveTypeLine;
    case PrimitiveType::LINE_STRIP:
      return MTL::PrimitiveTypeLineStrip;
    case PrimitiveType::TRIANGLE:
      return MTL::PrimitiveTypeTriangle;
    case PrimitiveType::TRIANGLE_STRIP:
      return MTL::PrimitiveTypeTriangleStrip;
  }
}

}  // namespace test_app::gfx