""

load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "StreamFormat",
    srcs = glob([ "src/**/*.h", "src/**/*.cpp" ]),
    hdrs = glob([ "src/**/*.h" ]),
    includes = [ "src/" ],
    copts = select({
        "@rules_cc//cc/compiler:msvc-cl": ["/std:c++20"],
        "//conditions:default": ["-std=c++20"],
    }),
    strip_include_prefix = "src",
    include_prefix = "StreamFormat",
    linkstatic = True,
    visibility = ["//visibility:public"],
)

cc_test(
    name = "StreamFormatTests",
    includes = [ "src/" ],
    srcs = glob([ "Tests/**/*.h", "Tests/**/*.cpp" ]),
    copts = select({
        "@rules_cc//cc/compiler:msvc-cl": ["/std:c++20"],
        "//conditions:default": ["-std=c++20"],
    }),
    deps = [ ":StreamFormat" ],
    visibility = ["//visibility:public"],
)

refresh_compile_commands(
    name = "refresh_compile_commands",
    exclude_external_sources = True,
    exclude_headers = "external",
    targets = {
        "//:StreamFormat": "",
    },
)
