load("@bazel_skylib//lib:selects.bzl", "selects")
load("//rules:metal.bzl", "metal_library")

package(default_visibility = ["//test_app:__subpackages__"])

cc_library(
    name = "camera",
    srcs = ["camera.cpp"],
    hdrs = ["camera.hpp"],
    copts = ["-std=c++17"],
    deps = ["@glm"],
)

cc_library(
    name = "material",
    srcs = ["material.cpp"],
    hdrs = ["material.hpp"],
    copts = ["-std=c++17"],
    deps = ["@entt"],
)

cc_library(
    name = "mesh_renderer",
    srcs = ["mesh_renderer.cpp"],
    hdrs = ["mesh_renderer.hpp"],
    copts = ["-std=c++17"],
    deps = ["@entt"],
)

cc_library(
    name = "mesh",
    srcs = ["mesh.cpp"],
    hdrs = ["mesh.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":primitive",
        ":vertex_descriptor",
    ],
)

cc_library(
    name = "primitive",
    srcs = ["primitive.cpp"],
    hdrs = ["primitive.hpp"],
    copts = ["-std=c++17"],
    deps = [":primitive_type"],
)

cc_library(
    name = "primitive_type",
    hdrs = ["primitive_type.hpp"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "renderer",
    hdrs = ["renderer.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:graphics_defines",
    ] + select({
        "//config/graphics:metal": ["//test_app/gfx/metal:renderer"],
        "//config/graphics:opengl": ["//test_app/gfx/gl:renderer"],
        "//config/graphics:opengles": ["//test_app/gfx/gl:renderer"],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "scene",
    srcs = ["scene.cpp"],
    hdrs = ["scene.hpp"],
    copts = ["-std=c++17"],
    deps = ["@entt"],
)

cc_library(
    name = "shader",
    hdrs = ["shader.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:graphics_defines",
    ] + select({
        "//config/graphics:metal": ["//test_app/gfx/metal:shader"],
        "//config/graphics:opengl": ["//test_app/gfx/gl:shader"],
        "//config/graphics:opengles": ["//test_app/gfx/gl:shader"],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "surface",
    hdrs = ["surface.hpp"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:platform_defines",
    ] + selects.with_or({
        (
            "//config/platform:appkit",
            "//config/platform:uikit",
        ): ["//test_app/gfx/apple:surface"],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "transform",
    srcs = ["transform.cpp"],
    hdrs = ["transform.hpp"],
    copts = ["-std=c++17"],
    deps = ["@glm"],
)

cc_library(
    name = "vertex_descriptor",
    srcs = ["vertex_descriptor.cpp"],
    hdrs = ["vertex_descriptor.hpp"],
    copts = ["-std=c++17"],
    deps = [":vertex_member"],
)

cc_library(
    name = "vertex_member",
    hdrs = ["vertex_member.hpp"],
    copts = ["-std=c++17"],
    deps = [":vertex_member_type"],
)

cc_library(
    name = "vertex_member_type",
    hdrs = ["vertex_member_type.hpp"],
    copts = ["-std=c++17"],
)

metal_library(
    name = "vertex_member_type_metal",
    hdrs = ["vertex_member_type.hpp"],
)
