""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "bazel_utilities",
    strip_prefix = "bazel_utilities-feature-compiler_paths",
    urls = [ "https://github.com/0-Sacha/bazel_utilities/archive/refs/heads/feature/compiler_paths.zip" ],
)

http_archive(
    name = "bazel_buildbuddy",
    strip_prefix = "bazel_buildbuddy-feature-init",
    urls = [ "https://github.com/0-Sacha/bazel_buildbuddy/archive/refs/heads/feature/init.zip" ],
)

load("@bazel_buildbuddy//:rules.bzl", "buildbuddy_toolchain")

buildbuddy_toolchain(
    name = "buildbuddy_test",
    auto_register_toolchain = False
)
