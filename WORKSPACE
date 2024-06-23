""

local_repository(
    name = "bazel_utilities",
    path = "./bazel_utilities"
)

local_repository(
    name = "bazel_winlibs_mingw",
    path = "./bazel_winlibs_mingw"
)

local_repository(
    name = "bazel_buildbuddy",
    path = "./bazel_buildbuddy",
)

load("@bazel_buildbuddy//:rules.bzl", "buildbuddy_toolchain")

buildbuddy_toolchain(
    name = "toolchain_ci_buildbuddy",
    auto_register_toolchain = False
)

load("@bazel_winlibs_mingw//:rules.bzl", "winlibs_mingw_toolchain")

winlibs_mingw_toolchain(
    name = "toolchain_ci_mingw",
    auto_register_toolchain = False
)
