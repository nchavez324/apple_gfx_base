#include <mach/mach_time.h>

#include "test_app/common/time.hpp"

namespace test_app {

uint64_t system_time_nanos() { return mach_absolute_time(); }

}  // namespace test_app
