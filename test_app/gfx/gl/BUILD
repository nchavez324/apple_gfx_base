package(default_visibility = ["//test_app:__subpackages__"])

cc_library(
    name = "bindings_open_gl",
    srcs = ["bindings_open_gl.cpp"],
    hdrs = ["bindings.h"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:platform_defines",
        "//third_party/apple_cpp:AppKit",
    ],
)

cc_library(
    name = "bindings_open_gles",
    srcs = ["bindings_open_gles.cpp"],
    hdrs = ["bindings.h"],
    copts = ["-std=c++17"],
    deps = [
        "//test_app/common:platform_defines",
        "//third_party/apple_cpp:OpenGLES",
        "//third_party/apple_cpp:QuartzCore_OpenGLES",
    ],
)

alias(
    name = "bindings",
    actual = select({
        "//config/graphics:opengl": ":bindings_open_gl",
        "//config/graphics:opengles": ":bindings_open_gles",
        "//conditions:default": ":bindings_open_gl",
    }),
)

cc_library(
    name = "material_buffer",
    srcs = ["material_buffer.cpp"],
    hdrs = ["material_buffer.hpp"],
    copts = ["-std=c++17"],
    defines = [
        "GL_SILENCE_DEPRECATION",
        "GLES_SILENCE_DEPRECATION",
    ],
    deps = [
        ":bindings",
        "//test_app/common:error_or",
        "//test_app/gfx:material",
        "//test_app/gfx:shader",
    ],
)

cc_library(
    name = "mesh_buffer",
    srcs = ["mesh_buffer.cpp"],
    hdrs = ["mesh_buffer.hpp"],
    copts = ["-std=c++17"],
    defines = [
        "GL_SILENCE_DEPRECATION",
        "GLES_SILENCE_DEPRECATION",
    ],
    deps = [
        ":bindings",
        "//test_app/common:error_or",
        "//test_app/common:graphics_defines",
        "//test_app/gfx:mesh",
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
        ":uniform_types",
        "//test_app/common:error",
        "//test_app/common:graphics_defines",
        "//test_app/gfx:camera",
        "//test_app/gfx:material",
        "//test_app/gfx:mesh",
        "//test_app/gfx:mesh_renderer",
        "//test_app/gfx:scene",
        "//test_app/gfx:surface",
        "//test_app/gfx:transform",
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
