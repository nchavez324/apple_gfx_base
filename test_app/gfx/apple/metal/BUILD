package(default_visibility = ["//test_app/gfx:__subpackages__"])

cc_library(
    name = "surface",
    srcs = ["surface.cpp"],
    hdrs = ["surface.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:error",
        "//test_app/gfx/apple:bindings",
        "//third_party/apple_cpp:Metal",
        "//third_party/apple_cpp:QuartzCore_Metal",
        "@glm",
    ],
)
