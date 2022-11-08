load("@build_bazel_rules_apple//apple:ios.bzl", "ios_application")
load("@build_bazel_rules_apple//apple:macos.bzl", "macos_application")
load("@build_bazel_rules_apple//apple:tvos.bzl", "tvos_application")

macos_application(
    name = "test_app_macos",
    bundle_id = "com.nickchavez.gfx-playground.test-app",
    infoplists = ["//test_app/entry/appkit:Info.plist"],
    # Metal introduced in 10.11
    # <filesystem> path in 10.15 though
    minimum_os_version = "10.15",
    deps = ["//test_app/entry/appkit:main"],
)

genrule(
    name = "test_app_macos_unzipped",
    srcs = [":test_app_macos.zip"],
    outs = ["test_app_macos_unzipped_dir"],
    cmd = "unzip $(location :test_app_macos.zip) -d $@",
)

ios_application(
    name = "test_app_ios",
    bundle_id = "com.nickchavez.gfx-playground.test-app",
    families = [
        "iphone",
        "ipad",
    ],
    infoplists = ["//test_app/entry/uikit/ios:Info.plist"],
    # Metal introduced in 8.0
    # <filesystem> path in 13.0 though
    # TODO: Enforce minimum of 13.0 for simulators
    minimum_os_version = "13.0",
    provisioning_profile = "//profiles:ios.mobileprovision",
    deps = ["//test_app/entry/uikit:main"],
)

tvos_application(
    name = "test_app_tvos",
    bundle_id = "com.nickchavez.gfx-playground.test-app",
    infoplists = ["//test_app/entry/uikit/tvos:Info.plist"],
    # Metal introduced in 8.0
    # <filesystem> path in 13.0 though
    # TODO: Enforce minimum of 13.0 for simulators
    minimum_os_version = "13.0",
    deps = ["//test_app/entry/uikit:main"],
)

refresh_compile_commands(
    name = "refresh_compile_commands",
    # Specify the targets of interest.
    # For example, specify a dict of targets and their arguments:
    targets = {
      "//test_app:test_app_macos": "--//config/graphics=opengl",
      "//test_app:test_app_ios": "--//config/graphics=opengles",
    },
    # For more details, feel free to look into refresh_compile_commands.bzl if you want.
)
