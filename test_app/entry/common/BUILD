package(default_visibility = ["//test_app/entry:__subpackages__"])

objc_library(
    name = "defines",
    hdrs = ["ARSDefines.h"],
)

objc_library(
    name = "surface_provider",
    hdrs = ["surface_provider.h"],
    copts = [
        "-ObjC++",
        "-std=c++17",
    ],
    deps = [
        ":defines",
        ":surface_view",
        "//test_app/gfx:surface",
    ],
)

objc_library(
    name = "surface_view",
    hdrs = ["ARSSurfaceView.h"],
    deps = select({
        "//config/platform:appkit": ["//test_app/entry/appkit:surface_view"],
        "//config/platform:uikit": ["//test_app/entry/uikit:surface_view"],
        "//conditions:default": ["//test_app/entry/appkit:surface_view"],
    }),
)

objc_library(
    name = "surface_view_delegate",
    hdrs = ["ARSSurfaceViewDelegate.h"],
    deps = ["//test_app/input:event"],
)

objc_library(
    name = "view_controller",
    srcs = ["ARSTViewController.mm"],
    hdrs = ["ARSTViewController.h"],
    copts = [
        "-ObjC++",
        "-std=c++17",
    ],
    deps = [
        ":defines",
        ":surface_provider",
        ":surface_view_delegate",
        "//test_app/app",
        "//third_party/apple_cpp:Foundation",
        "@glm",
    ],
)
