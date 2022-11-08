#ifndef TEST_APP_COMMON_ERROR_OR_H
#define TEST_APP_COMMON_ERROR_OR_H

#include <variant>

#include "test_app/common/error.hpp"

namespace test_app {

template <typename T>
class ErrorOr : std::variant<Error, T> {
 public:
  ErrorOr<T>(const Error &error) : std::variant<Error, T>(error) {}
  ErrorOr<T>(Error &&error) : std::variant<Error, T>(std::move(error)) {}

  ErrorOr<T>(const T &t) : std::variant<Error, T>(t) {}
  ErrorOr<T>(T &&t) : std::variant<Error, T>(std::move(t)) {}

  bool ok() const { return !std::holds_alternative<Error>(*this); }
  const Error &error() const { return std::get<Error>(*this); }
  T &value() { return std::get<T>(*this); }

  T &operator*() { return std::get<T>(*this); }
  T *operator->() { return &(std::get<T>(*this)); }
};

}  // namespace test_app

#endif  // TEST_APP_COMMON_ERROR_OR_H
