#ifndef TEST_APP_GFX_PRIMITIVE_H
#define TEST_APP_GFX_PRIMITIVE_H

#include <vector>

#include "test_app/gfx/primitive_type.hpp"

namespace test_app::gfx {

class Primitive {
 public:
  explicit Primitive(PrimitiveType type, size_t index_size, size_t index_count,
                     const void *index_buffer);
  Primitive(const Primitive &) = delete;
  Primitive(Primitive &&);
  Primitive &operator=(const Primitive &) = delete;
  Primitive &operator=(Primitive &&);
  ~Primitive();

  PrimitiveType type() const;
  size_t index_count() const;
  size_t index_size() const;
  const void *index_buffer() const;
  size_t index_buffer_size() const;

 protected:
  PrimitiveType type_;
  size_t index_size_;
  size_t index_count_;
  void *index_buffer_;
};
}  // namespace test_app::gfx

#endif  // TEST_APP_GFX_PRIMITIVE_H
