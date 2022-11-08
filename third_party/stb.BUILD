cc_library(
    name = "stb_image",
    hdrs = ["stb_image.h"],
    tags = ["swift_module=stb_image"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "stb_image_impl",
    srcs = [":stb_image_impl.c"],
    hdrs = ["stb_image.h"],
    tags = ["swift_module=stb_image"],
    visibility = ["//visibility:public"],
)

STB_IMAGE_IMPL_SRC = """
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
"""

genrule(
    name = "stb_image_impl_c",
    srcs = [],
    outs = [
        "stb_image_impl.c",
    ],
    cmd = "echo '" + STB_IMAGE_IMPL_SRC + "' > $@",
)
