load("@bazel_skylib//lib:selects.bzl", "selects")

selects.config_setting_group(
    name = "appkit",
    match_any = [
        "@build_bazel_rules_apple//apple:darwin_x86_64",
        "@build_bazel_rules_apple//apple:darwin_arm64",
        "@build_bazel_rules_apple//apple:darwin_arm64e",
    ],
)

selects.config_setting_group(
    name = "uikit",
    match_any = [
        "@build_bazel_rules_apple//apple:ios_i386",
        "@build_bazel_rules_apple//apple:ios_x86_64",
        "@build_bazel_rules_apple//apple:ios_armv7",
        "@build_bazel_rules_apple//apple:ios_arm64",
        "@build_bazel_rules_apple//apple:ios_sim_arm64",
        "@build_bazel_rules_apple//apple:tvos_x86_64",
        "@build_bazel_rules_apple//apple:tvos_arm64",
    ],
)
