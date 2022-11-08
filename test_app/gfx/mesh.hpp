#ifndef TEST_APP_GFX_MESH_H
#define TEST_APP_GFX_MESH_H

#include <vector>

#include "test_app/gfx/primitive.hpp"
#include "test_app/gfx/vertex_descriptor.hpp"

namespace test_app::gfx {

/**
 * The CPU representation of mesh data. Internally, the Renderer will attach a
 * graphics API specific MeshBuffer component to entities with this component to
 * upload this to the GPU.
 * To draw this mesh, a MeshRender component must be pointing to an entity with
 * this component.
 */
class Mesh {
 public:
  Mesh(Primitive primitive, VertexDescriptor vertex_descriptor,
       size_t vertex_count, const void *vertex_buffer);
  Mesh(const Mesh &) = delete;
  Mesh(Mesh &&);
  Mesh &operator=(const Mesh &) = delete;
  Mesh &operator=(Mesh &&);
  ~Mesh();

  const Primitive &primitive() const;
  const VertexDescriptor &vertex_descriptor() const;
  size_t vertex_count() const;
  const void *vertex_buffer() const;
  size_t vertex_buffer_size() const;

 protected:
  Primitive primitive_;
  VertexDescriptor vertex_descriptor_;
  size_t vertex_count_;
  void *vertex_buffer_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_MESH_H
