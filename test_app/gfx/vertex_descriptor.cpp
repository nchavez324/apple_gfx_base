#include "test_app/gfx/vertex_descriptor.hpp"

namespace test_app::gfx {

VertexDescriptor::VertexDescriptor(std::vector<VertexMember> members,
                                   size_t size)
    : members_{std::move(members)}, size_{size} {}

const std::vector<VertexMember> &VertexDescriptor::members() const {
  return members_;
}

size_t VertexDescriptor::size() const { return size_; }

}  // namespace test_app::gfx