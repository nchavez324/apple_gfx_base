package(default_visibility = ["//test_app/gfx:__subpackages__"])

cc_library(
    name = "surface",
    srcs = ["surface.cpp"],
    hdrs = ["surface.hpp"],
    copts = ["-std=c++17"],
    defines = [
        "GL_SILENCE_DEPRECATION",
        "GLES_SILENCE_DEPRECATION",
    ],
    deps = [
        "//test_app/common:error",
        "//test_app/gfx/apple:bindings",
        "//test_app/gfx/gl:bindings",
        "//third_party/apple_cpp:OpenGLES",
        "//third_party/apple_cpp:QuartzCore_OpenGLES",
        "@glm",
    ],
)
