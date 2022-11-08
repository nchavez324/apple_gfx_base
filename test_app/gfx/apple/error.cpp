#include "test_app/gfx/apple/error.hpp"

#include <cassert>

namespace test_app::gfx::apple {

Error errorFromNSError(NS::Error *error) {
  assert(error);
  return Error(ErrorCode::UNIMPLEMENTED,
               error->localizedDescription()->cString(NS::ASCIIStringEncoding));
}

}  // namespace test_app::gfx::apple
