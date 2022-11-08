#ifndef TEST_APP_GFX_METAL_MESH_BUFFER_H
#define TEST_APP_GFX_METAL_MESH_BUFFER_H

#include <optional>

#include "test_app/common/error_or.hpp"
#include "test_app/gfx/mesh.hpp"
#include "third_party/apple_cpp/Foundation/Foundation.hpp"
#include "third_party/apple_cpp/Metal/Metal.hpp"

namespace test_app::gfx {

/**
 * The Metal GPU representation of mesh data. Internally, the Renderer will
 * create a MeshBuffer component for each Mesh component.
 * To draw this mesh, a MeshRenderer component must be pointing to the
 * this entity with this component.
 */
class MeshBuffer {
 public:
  static ErrorOr<MeshBuffer> Build(MTL::Device *device, const Mesh &mesh);

  MeshBuffer(MTL::Buffer *vertex_buffer, MTL::Buffer *index_buffer,
             MTL::PrimitiveType primitive_type, MTL::IndexType index_type,
             size_t index_count);
  MeshBuffer(const MeshBuffer &) = delete;
  MeshBuffer(MeshBuffer &&);
  MeshBuffer &operator=(const MeshBuffer &) = delete;
  MeshBuffer &operator=(MeshBuffer &&);
  ~MeshBuffer();

  MTL::Buffer *vertex_buffer();
  MTL::Buffer *index_buffer();
  MTL::PrimitiveType primitive_type() const;
  MTL::IndexType index_type() const;
  size_t index_count() const;

  void set_version(std::uint32_t);

 private:
  MTL::Buffer *vertex_buffer_;
  MTL::Buffer *index_buffer_;
  MTL::PrimitiveType primitive_type_;
  MTL::IndexType index_type_;
  size_t index_count_;

  static std::optional<MTL::IndexType> MTLIndexTypeFromIndexSize(size_t);
  static MTL::PrimitiveType MTLPrimitiveTypeFromPrimitiveType(
      gfx::PrimitiveType);
};
}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_METAL_MESH_BUFFER_H
