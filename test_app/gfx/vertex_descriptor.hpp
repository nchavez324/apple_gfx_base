#ifndef TEST_APP_GFX_VERTEX_DESCRIPTOR_H
#define TEST_APP_GFX_VERTEX_DESCRIPTOR_H

#include <vector>

#include "test_app/gfx/vertex_member.hpp"

namespace test_app::gfx {

class VertexDescriptor {
 public:
  VertexDescriptor(std::vector<VertexMember> members, size_t size);
  VertexDescriptor(const VertexDescriptor &) = default;
  VertexDescriptor(VertexDescriptor &&) = default;
  VertexDescriptor &operator=(const VertexDescriptor &) = default;
  VertexDescriptor &operator=(VertexDescriptor &&) = default;
  ~VertexDescriptor() = default;

  const std::vector<VertexMember> &members() const;
  size_t size() const;

 protected:
  std::vector<VertexMember> members_;
  size_t size_;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_VERTEX_DESCRIPTOR_H
