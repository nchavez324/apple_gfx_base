package(default_visibility = ["//test_app/entry:__subpackages__"])

objc_library(
    name = "metal",
    srcs = glob([
        "*.m",
        "*.mm",
    ]),
    hdrs = glob(["*.h"]),
    copts = [
        "-ObjC++",
        "-std=c++17",
    ],
    sdk_frameworks = [
        "Metal",
        "QuartzCore",
    ],
    deps = [
        "//test_app/entry/common:surface_provider",
        "//test_app/entry/common:surface_view",
        "//test_app/gfx/metal:renderer",
    ],
)
