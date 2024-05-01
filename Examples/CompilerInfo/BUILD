""

load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "CompilerInfo",
    srcs = glob([ "*.h", "*.cpp" ]),
    includes = [ "" ],
    deps = [ "@projectcore//:ProjectCore" ],
    visibility = ["//visibility:public"],
)
