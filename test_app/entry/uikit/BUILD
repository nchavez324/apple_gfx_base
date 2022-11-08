package(default_visibility = ["//test_app:__pkg__"])

objc_library(
    name = "main",
    srcs = [
        "ARSTAppDelegate.h",
        "ARSTAppDelegate.mm",
        "main.m",
    ],
    copts = [
        "-ObjC++",
        "-std=c++17",
    ],
    data = ["//test_app/app:resources"],
    sdk_frameworks = [
        "CoreGraphics",
        "Foundation",
        "QuartzCore",
        "UIKit",
    ],
    deps = [
        "//test_app/entry/common:view_controller",
    ] + select({
        "//config/graphics:metal": ["//test_app/entry/metal"],
        "//config/graphics:opengl": ["//test_app/entry/gl"],
        "//config/graphics:opengles": ["//test_app/entry/gl"],
    }),
)

objc_library(
    name = "surface_view",
    srcs = ["ARSSurfaceView.mm"],
    hdrs = ["ARSSurfaceView.h"],
    copts = [
        "-ObjC++",
        "-std=c++17",
    ],
    defines = [
        "GL_SILENCE_DEPRECATION",
        "GLES_SILENCE_DEPRECATION",
    ],
    sdk_frameworks = [
        "CoreGraphics",
        "Foundation",
        "QuartzCore",
        "UIKit",
    ],
    visibility = ["//test_app/entry:__subpackages__"],
    deps = ["//test_app/entry/common:surface_view_delegate"],
)
