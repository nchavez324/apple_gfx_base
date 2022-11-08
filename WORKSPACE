load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
  name = "platforms",
  remote = "https://github.com/bazelbuild/platforms.git",
  # tag = "0.0.4",
  commit = "d4c9d7f51a7c403814b60f66d20eeb425fbaaacb",
  shallow_since = "1614258450 -0800",
)

http_archive(
  name = "build_bazel_rules_apple",
  sha256 = "4161b2283f80f33b93579627c3bd846169b2d58848b0ffb29b5d4db35263156a",
  url = "https://github.com/bazelbuild/rules_apple/releases/download/0.34.0/rules_apple.0.34.0.tar.gz",
)

load("@build_bazel_rules_apple//apple:repositories.bzl", "apple_rules_dependencies")
apple_rules_dependencies()

load("@build_bazel_rules_swift//swift:repositories.bzl", "swift_rules_dependencies")
swift_rules_dependencies()

load("@build_bazel_rules_swift//swift:extras.bzl", "swift_rules_extra_dependencies")
swift_rules_extra_dependencies()

load("@build_bazel_apple_support//lib:repositories.bzl", "apple_support_dependencies")
apple_support_dependencies()

http_archive(
  name = "hedron_compile_commands",
  url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/ba1751e3bb9865df2d4661ca778b0cd4ffd1fb10.tar.gz",
  strip_prefix = "bazel-compile-commands-extractor-ba1751e3bb9865df2d4661ca778b0cd4ffd1fb10",
  sha256 = "9711de4935a68cbaba9ad79ac4e69a8028c8ef1446ede4469017b676cefe9140",
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()

http_archive(
  name = "glm",
  build_file = "@//third_party:glm.BUILD",
  strip_prefix = "glm",
  url = "https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip",
  sha256 = "37e2a3d62ea3322e43593c34bae29f57e3e251ea89f4067506c94043769ade4c",
)

http_archive(
  name = "stb",
  build_file = "@//third_party:stb.BUILD",
  strip_prefix = "stb-af1a5bc352164740c1cc1354942b1c6b72eacb8a",
  url = "https://github.com/nothings/stb/archive/af1a5bc352164740c1cc1354942b1c6b72eacb8a.zip",
  sha256 = "e3d0edbecd356506d3d69b87419de2f9d180a98099134c6343177885f6c2cbef",
)

git_repository(
  name = "entt",
  remote = "https://github.com/skypjack/entt.git",
  # tag = "v3.9.0",
  commit = "8e0747fd505beb6861939a141ec0962c376d36f2",
  shallow_since = "1640071968 +0100",
)
