#include "test_app/gfx/primitive.hpp"

namespace test_app::gfx {

Primitive::Primitive(PrimitiveType type, size_t index_size, size_t index_count,
                     const void *index_buffer)
    : type_{type},
      index_size_{index_size},
      index_count_{index_count},
      index_buffer_{malloc(index_size * index_count)} {
  memcpy(index_buffer_, index_buffer, index_size * index_count);
}

Primitive::Primitive(Primitive &&from)
    : type_{from.type_},
      index_size_{from.index_size_},
      index_count_{from.index_count_},
      index_buffer_{from.index_buffer_} {
  from.index_count_ = 0;
  from.index_buffer_ = nullptr;
}

Primitive &Primitive::operator=(Primitive &&from) {
  this->type_ = from.type_;
  this->index_size_ = from.index_size_;
  this->index_count_ = from.index_count_;
  from.index_count_ = 0;
  this->index_buffer_ = from.index_buffer_;
  from.index_buffer_ = nullptr;
  return *this;
}

Primitive::~Primitive() {
  if (index_buffer_ != nullptr) free(index_buffer_);
}

PrimitiveType Primitive::type() const { return type_; }
size_t Primitive::index_count() const { return index_count_; }
size_t Primitive::index_size() const { return index_size_; }
const void *Primitive::index_buffer() const { return index_buffer_; }
size_t Primitive::index_buffer_size() const {
  return index_count_ * index_size_;
}

}  // namespace test_app::gfx
