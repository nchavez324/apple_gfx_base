#include "test_app/common/error.hpp"

namespace test_app {

const char *ErrorCodeToString(ErrorCode code) {
  switch (code) {
    case ErrorCode::INVALID_ARGUMENT:
      return "InvalidArgument";
    case ErrorCode::NOT_FOUND:
      return "NotFound";
    case ErrorCode::DEADLINE_EXCEEDED:
      return "DeadlineExceeded";
    case ErrorCode::RESOURCE_EXHAUSTED:
      return "ResourceExhausted";
    case ErrorCode::FAILED_PRECONDITION:
      return "FailedPrecondition";
    case ErrorCode::OUT_OF_RANGE:
      return "OutOfRange";
    case ErrorCode::UNIMPLEMENTED:
      return "Unimplemented";
    case ErrorCode::UNAVAILABLE:
      return "Unavailable";
    case ErrorCode::UNKNOWN:
      return "Unknown";
    default:
      return "Undefined";
  }
}

Error::Error(ErrorCode code, std::string_view message)
    : code_{code}, message_{message} {}

ErrorCode Error::code() const { return code_; }

const std::string &Error::message() const { return message_; }

std::ostream &operator<<(std::ostream &stream, const Error &error) {
  return stream << "Error{ code: " << ErrorCodeToString(error.code_)
                << ", msg: " << error.message_ << " }";
}

Error Error::InvalidArgument(std::string_view message) {
  return Error(ErrorCode::INVALID_ARGUMENT, message);
}

Error Error::NotFound(std::string_view message) {
  return Error(ErrorCode::NOT_FOUND, message);
}

Error Error::Unknown(std::string_view message) {
  return Error(ErrorCode::UNKNOWN, message);
}

Error Error::DeadlineExceeded(std::string_view message) {
  return Error(ErrorCode::DEADLINE_EXCEEDED, message);
}

Error Error::ResourceExhausted(std::string_view message) {
  return Error(ErrorCode::RESOURCE_EXHAUSTED, message);
}

Error Error::FailedPrecondition(std::string_view message) {
  return Error(ErrorCode::FAILED_PRECONDITION, message);
}

Error Error::OutOfRange(std::string_view message) {
  return Error(ErrorCode::OUT_OF_RANGE, message);
}

Error Error::Unimplemented(std::string_view message) {
  return Error(ErrorCode::UNIMPLEMENTED, message);
}

Error Error::Unavailable(std::string_view message) {
  return Error(ErrorCode::UNAVAILABLE, message);
}

}  // namespace test_app
