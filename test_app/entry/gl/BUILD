package(default_visibility = ["//test_app/entry:__subpackages__"])

SDK_FRAMEWORKS_APPKIT = [
    "AppKit",
    "Foundation",
    "OpenGL",
]

SDK_FRAMEWORKS_UIKIT = [
    "Foundation",
    "OpenGLES",
    "UIKit",
]

objc_library(
    name = "gl",
    srcs = glob([
        "*.m",
        "*.mm",
    ]),
    hdrs = glob(["*.h"]),
    copts = [
        "-ObjC++",
        "-std=c++17",
    ],
    defines = [
        "GL_SILENCE_DEPRECATION",
        "GLES_SILENCE_DEPRECATION",
    ],
    sdk_frameworks = select({
        "//config/platform:appkit": SDK_FRAMEWORKS_APPKIT,
        "//config/platform:uikit": SDK_FRAMEWORKS_UIKIT,
        "//conditions:default": SDK_FRAMEWORKS_APPKIT,
    }),
    deps = [
        "//test_app/entry/common:surface_provider",
        "//test_app/entry/common:surface_view",
        "//test_app/gfx/gl:renderer",
    ],
)
