""
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "BazelUtilities",
    remote = "https://github.com/0-Sacha/BazelUtilities.git",
    branch = "main"
)

load("@BazelUtilities//toolchains/MinGW:MinGW.bzl", "MinGW_deps", "mingw_gcc_toolchain")

MinGW_deps()
mingw_gcc_toolchain.register()
register_toolchains("toolchain_mingw_gcc-localhost-localhost")
