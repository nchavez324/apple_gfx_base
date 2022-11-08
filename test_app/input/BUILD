package(default_visibility = ["//test_app:__subpackages__"])

cc_library(
    name = "buffer",
    srcs = ["buffer.cpp"],
    hdrs = ["buffer.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":button_event",
        ":event",
        ":pointer_event",
        ":state",
    ],
)

cc_library(
    name = "button",
    hdrs = ["button.hpp"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "button_event",
    srcs = ["button_event.cpp"],
    hdrs = ["button_event.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":button",
        ":event",
    ],
)

cc_library(
    name = "event",
    srcs = ["event.cpp"],
    hdrs = ["event.hpp"],
    copts = ["-std=c++17"],
)

cc_library(
    name = "pointer_event",
    srcs = ["pointer_event.cpp"],
    hdrs = ["pointer_event.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":event",
        "@glm",
    ],
)

cc_library(
    name = "state",
    hdrs = ["state.hpp"],
    copts = ["-std=c++17"],
    deps = [
        ":button",
        "@glm",
    ],
)
