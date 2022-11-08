load("//rules:metal.bzl", "metal_library")

package(default_visibility = ["//test_app:__subpackages__"])

cc_library(
    name = "bindings",
    srcs = ["bindings.cpp"],
    copts = ["-std=c++17"],
    deps = [
        "//third_party/apple_cpp:CoreGraphics",
        "//third_party/apple_cpp:Metal",
        "//third_party/apple_cpp:QuartzCore_Metal",
    ],
)

cc_library(
    name = "material_buffer",
    srcs = ["material_buffer.cpp"],
    hdrs = ["material_buffer.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:error_or",
        "//test_app/gfx:material",
        "//test_app/gfx:shader",
        "//test_app/gfx/apple:error",
        "//third_party/apple_cpp:Metal",
    ],
)

cc_library(
    name = "mesh_buffer",
    srcs = ["mesh_buffer.cpp"],
    hdrs = ["mesh_buffer.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:error_or",
        "//test_app/gfx:mesh",
        "//third_party/apple_cpp:Metal",
    ],
)

cc_library(
    name = "renderer",
    srcs = ["renderer.cpp"],
    hdrs = ["renderer.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":bindings",
        ":material_buffer",
        ":mesh_buffer",
        ":shader",
        ":uniform_types",
        "//test_app/common:error",
        "//test_app/gfx:camera",
        "//test_app/gfx:material",
        "//test_app/gfx:mesh",
        "//test_app/gfx:mesh_renderer",
        "//test_app/gfx:scene",
        "//test_app/gfx:surface",
        "//test_app/gfx:transform",
        "//test_app/gfx/apple:bindings",
        "//test_app/gfx/apple:error",
        "//test_app/gfx/apple:math",
        "//third_party/apple_cpp:Foundation",
        "//third_party/apple_cpp:Metal",
        "//third_party/apple_cpp:QuartzCore_Metal",
        "@glm",
        "@stb//:stb_image",
    ],
)

cc_library(
    name = "shader",
    srcs = ["shader.cpp"],
    hdrs = ["shader.hpp"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "uniform_types",
    hdrs = ["uniform_types.hpp"],
    copts = ["-std=c++17"],
)

metal_library(
    name = "uniform_types_metal",
    hdrs = ["uniform_types.hpp"],
)
