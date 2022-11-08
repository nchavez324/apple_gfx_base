#ifndef TEST_APP_COMMON_ERROR_H
#define TEST_APP_COMMON_ERROR_H

#include <iostream>
#include <string>

namespace test_app {

enum class ErrorCode {
  INVALID_ARGUMENT,
  NOT_FOUND,
  UNKNOWN,
  DEADLINE_EXCEEDED,
  RESOURCE_EXHAUSTED,
  FAILED_PRECONDITION,
  OUT_OF_RANGE,
  UNIMPLEMENTED,
  UNAVAILABLE,
};

const char *ErrorCodeToString(ErrorCode code);

class Error {
 public:
  Error(ErrorCode code, std::string_view message);

  ErrorCode code() const;
  const std::string &message() const;

  friend std::ostream &operator<<(std::ostream &stream, const Error &error);

  static Error InvalidArgument(std::string_view message);
  static Error NotFound(std::string_view message);
  static Error Unknown(std::string_view message);
  static Error DeadlineExceeded(std::string_view message);
  static Error ResourceExhausted(std::string_view message);
  static Error FailedPrecondition(std::string_view message);
  static Error OutOfRange(std::string_view message);
  static Error Unimplemented(std::string_view message);
  static Error Unavailable(std::string_view message);

 private:
  ErrorCode code_;
  std::string message_;
};

}  // namespace test_app

#endif  // TEST_APP_COMMON_ERROR_H
