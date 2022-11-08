#ifndef TEST_APP_GFX_APPLE_ERROR_H
#define TEST_APP_GFX_APPLE_ERROR_H

#include <string>

#include "test_app/common/error.hpp"
#include "third_party/apple_cpp/Foundation/Foundation.hpp"

namespace test_app::gfx::apple {

Error errorFromNSError(NS::Error *error);

}  // namespace test_app::gfx::apple

#endif  // TEST_APP_GFX_APPLE_ERROR_H
