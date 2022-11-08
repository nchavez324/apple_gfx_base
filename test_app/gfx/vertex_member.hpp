#ifndef TEST_APP_GFX_VERTEX_MEMBER_H
#define TEST_APP_GFX_VERTEX_MEMBER_H

#include <vector>

#include "test_app/gfx/vertex_member_type.hpp"

namespace test_app::gfx {

struct VertexMember {
  VertexMember(const VertexMember &) = default;
  VertexMember(VertexMember &&) = delete;
  VertexMember &operator=(const VertexMember &) = delete;
  VertexMember &operator=(VertexMember &&) = delete;
  ~VertexMember() = default;

  const VertexMemberType type;
  const size_t size;
  const size_t offset;
};

}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_VERTEX_MEMBER_H
