load("//rules:metal.bzl", "metal_binary")

package(default_visibility = ["//test_app/app:__subpackages__"])

alias(
    name = "shaders",
    actual = select({
        "//config/graphics:metal": "//test_app/app/resources/shaders:metal",
        "//config/graphics:opengl": "//test_app/app/resources/shaders:opengl",
        "//config/graphics:opengles": "//test_app/app/resources/shaders:opengles",
        "//conditions:default": "//test_app/app/resources/shaders:opengl",
    }),
)

metal_binary(
    name = "metal",
    srcs = glob(["metal/*.metal"]),
    deps = [
        "//test_app/app:vertex_types_metal",
        "//test_app/gfx:vertex_member_type_metal",
        "//test_app/gfx/metal:uniform_types_metal",
    ],
)

filegroup(
    name = "opengl",
    srcs = glob([
        "opengl/*.frag",
        "opengl/*.vert",
    ]),
)

filegroup(
    name = "opengles",
    srcs = glob([
        "opengles/*.frag",
        "opengles/*.vert",
    ]),
)
