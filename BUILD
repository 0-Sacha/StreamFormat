""

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "ProjectCore",
    srcs = glob([ "src/**/*.h", "src/**/*.cpp" ]),
    hdrs = glob([ "src/**/*.h" ]),
    includes = [ "src/" ],
    strip_include_prefix = "src",
    include_prefix = "ProjectCore",
    visibility = ["//visibility:public"],
)

cc_test(
    name = "ProjectCoreTests",
    includes = [ "src/" ],
    srcs = glob([ "Tests/**/*.h", "Tests/**/*.cpp" ]),
    deps = [ ":ProjectCore" ],
    visibility = ["//visibility:public"],
)
