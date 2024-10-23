""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "bazel_utilities",
    strip_prefix = "bazel_utilities-7c379bd1b6a4ae0ff5123b63385f92fb527bd687",
    urls = [ "https://github.com/0-Sacha/bazel_utilities/archive/7c379bd1b6a4ae0ff5123b63385f92fb527bd687.zip" ],
)

http_archive(
    name = "bazel_buildbuddy",
    strip_prefix = "bazel_buildbuddy-b0840cf378c4aef5750b5e8bc87aa2ad1aeb874f",
    urls = [ "https://github.com/0-Sacha/bazel_buildbuddy/archive/b0840cf378c4aef5750b5e8bc87aa2ad1aeb874f.zip" ],
    integrity = "sha256-Wvbu4LB7F3d42Xj/dQyaGjVEntf4U3DO+aku3zEZD4I=",
)

http_archive(
    name = "bazel_winlibs_mingw",
    strip_prefix = "bazel_winlibs_mingw-09c1b538db4fa262bba152b24b7c1d61079e5abe",
    urls = [ "https://github.com/0-Sacha/bazel_winlibs_mingw/archive/09c1b538db4fa262bba152b24b7c1d61079e5abe.zip" ],
    integrity = "sha256-rxd9695aR8gQ7sOFiz1YUDURvdgqi+3o3GLygEVLuas="
)

load("@bazel_buildbuddy//:rules.bzl", "buildbuddy_toolchain")

buildbuddy_toolchain(
    name = "toolchain_ci_buildbuddy",
    auto_register_toolchain = False
)

load("@bazel_winlibs_mingw//:rules.bzl", "winlibs_mingw_toolchain")
# winlibs_mingw_toolchain(
#     "mingw",
#     copts = [ "-g", "-O0" ],
# )
