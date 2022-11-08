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
        "AppKit",
        "Cocoa",
        "CoreGraphics",
        "Foundation",
        "QuartzCore",
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
    name = "input_router",
    srcs = ["ARSInputRouter.mm"],
    hdrs = ["ARSInputRouter.h"],
    copts = [
        "-ObjC++",
        "-std=c++17",
    ],
    deps = [
        "//test_app/input:button",
        "//test_app/input:button_event",
        "//test_app/input:event",
        "//test_app/input:pointer_event",
    ],
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
        "AppKit",
        "CoreGraphics",
        "QuartzCore",
        "Foundation",
    ],
    visibility = ["//test_app/entry:__subpackages__"],
    deps = [
        ":input_router",
        "//test_app/common:graphics_defines",
        "//test_app/entry/common:surface_view_delegate",
    ],
)

exports_files([
    "Info.plist",
])
