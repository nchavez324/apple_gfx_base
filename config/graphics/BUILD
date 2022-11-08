load("@bazel_skylib//rules:common_settings.bzl", "string_flag")

string_flag(
    name = "graphics",
    build_setting_default = "metal",
    values = [
        "metal",
        "opengl",
        "opengles",
    ],
)

config_setting(
    name = "metal",
    flag_values = {
        ":graphics": "metal",
    },
)

config_setting(
    name = "opengl",
    flag_values = {
        ":graphics": "opengl",
    },
)

config_setting(
    name = "opengles",
    flag_values = {
        ":graphics": "opengles",
    },
)
