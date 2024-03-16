""

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "io_buildbuddy_buildbuddy_toolchain",
    remote  = "git@github.com:buildbuddy-io/buildbuddy-toolchain.git",
    branch = "master"
)

load("@io_buildbuddy_buildbuddy_toolchain//:deps.bzl", "buildbuddy_deps")

buildbuddy_deps()

load("@io_buildbuddy_buildbuddy_toolchain//:rules.bzl", "buildbuddy", "UBUNTU20_04_IMAGE")

buildbuddy(name = "buildbuddy_toolchain", container_image = UBUNTU20_04_IMAGE, llvm=True)
