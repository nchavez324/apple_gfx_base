load("//rules:metal.bzl", "metal_library")

package(default_visibility = ["//test_app/entry:__subpackages__"])

filegroup(
    name = "resources",
    srcs = [
        "resources/texture.jpg",
        "//test_app/app/resources/shaders",
    ],
)

cc_library(
    name = "app",
    srcs = ["app.cpp"],
    hdrs = ["app.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":math",
        ":mesh_builder",
        "//test_app/common:error",
        "//test_app/common:graphics_defines",
        "//test_app/common:semaphore",
        "//test_app/common:time",
        "//test_app/gfx:camera",
        "//test_app/gfx:material",
        "//test_app/gfx:mesh",
        "//test_app/gfx:mesh_renderer",
        "//test_app/gfx:renderer",
        "//test_app/gfx:scene",
        "//test_app/gfx:shader",
        "//test_app/gfx:surface",
        "//test_app/gfx:transform",
        "//test_app/input:buffer",
        "//test_app/input:button_event",
        "//test_app/input:event",
        "//test_app/input:pointer_event",
        "@glm",
    ],
)

cc_library(
    name = "mesh_builder",
    srcs = ["mesh_builder.cpp"],
    hdrs = ["mesh_builder.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":vertex_types",
        "//test_app/gfx:mesh",
        "//test_app/gfx:primitive",
        "//test_app/gfx:vertex_descriptor",
        "//test_app/gfx:vertex_member",
        "//test_app/gfx:vertex_member_type",
    ],
)

cc_library(
    name = "math",
    srcs = ["math.cpp"],
    hdrs = ["math.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "@glm",
    ],
)

cc_library(
    name = "vertex_types",
    hdrs = ["vertex_types.hpp"],
    deps = [
        "//test_app/gfx:vertex_descriptor",
        "//test_app/gfx:vertex_member",
        "//test_app/gfx:vertex_member_type",
    ],
)

metal_library(
    name = "vertex_types_metal",
    hdrs = ["vertex_types.hpp"],
    visibility = [
        "//test_app/app/resources/shaders:__subpackages__",
        "//test_app/entry:__subpackages__",
    ],
)
