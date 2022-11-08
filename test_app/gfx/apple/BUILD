package(default_visibility = ["//test_app/gfx:__subpackages__"])

cc_library(
    name = "bindings",
    srcs = ["bindings.cpp"],
    copts = ["-std=c++17"],
    deps = ["//third_party/apple_cpp:Foundation"],
)

cc_library(
    name = "error",
    srcs = ["error.cpp"],
    hdrs = ["error.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:error",
        "//third_party/apple_cpp:Foundation",
    ],
)

cc_library(
    name = "math",
    srcs = ["math.cpp"],
    hdrs = ["math.hpp"],
    copts = ["-std=c++17"],
    deps = ["@glm"],
)

cc_library(
    name = "surface",
    hdrs = ["surface.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:graphics_defines",
    ] + select({
        "//config/graphics:opengl": ["//test_app/gfx/apple/opengl:surface"],
        "//config/graphics:opengles": ["//test_app/gfx/apple/opengles:surface"],
        "//config/graphics:metal": ["//test_app/gfx/apple/metal:surface"],
        "//conditions:default": [],
    }),
)
