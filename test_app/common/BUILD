package(default_visibility = ["//test_app:__subpackages__"])

cc_library(
    name = "error",
    srcs = ["error.cpp"],
    hdrs = ["error.hpp"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "error_or",
    hdrs = ["error_or.hpp"],
    copts = ["-std=c++17"],
    deps = [":error"],
)

cc_library(
    name = "graphics_defines",
    hdrs = ["graphics_defines.h"],
    copts = ["-std=c++17"],
    defines = select({
        "//config/graphics:metal": ["_GFX_METAL=1"],
        "//config/graphics:opengl": ["_GFX_OPEN_GL=1"],
        "//config/graphics:opengles": ["_GFX_OPEN_GLES=1"],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "platform_defines",
    hdrs = ["platform_defines.h"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "semaphore",
    srcs = ["semaphore.cpp"],
    hdrs = ["semaphore.hpp"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "time",
    srcs = ["time_apple.cpp"],
    hdrs = ["time.hpp"],
    copts = ["-std=c++17"],
)
