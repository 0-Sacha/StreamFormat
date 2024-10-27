""

load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "CompilerInfo",
    srcs = glob([ "*.h", "*.cpp" ]),
    includes = [ "" ],
    copts = select({
        "@rules_cc//cc/compiler:msvc-cl": ["/std:c++20"],
        "//conditions:default": ["-std=c++20"],
    }),
    deps = [ "@streamformat//:StreamFormat" ],
    visibility = ["//visibility:public"],
)
