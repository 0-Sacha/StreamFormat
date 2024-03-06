""

load("@BazelUtilities//solutions:solutions.bzl", "solution_project_build", "solution_project_info", "ProjectType")
load("@BazelUtilities//toolchains/MinGW:MinGW.bzl", "mingw_gcc_toolchain")
load("@BazelUtilities//toolchains/MinGW:MinGW_localhost.bzl", "MinGW_gcc_localhost")

load(":project.bzl", "info_ProjectCore")

MinGW_gcc_localhost()
mingw_gcc_toolchain.gen()

solution_project_build(
    info = info_ProjectCore,
    hdrs = glob([ "src/**/*.h", "src/**/*.impl" ]),
    srcs = glob([ "src/**/*.h", "src/**/*.impl" ]) + glob([ "src/**/*.cpp" ])
)

# buildifier: disable=name-conventions
info_ProjectCoreTest = solution_project_info(
    name = "ProjectCoreTest",
    project_type = ProjectType.Test,
    project_deps = [ info_ProjectCore ],
    include_dirs = [ "Tests/" ],
    copts = [ "-std=c++20" ],
    linkopts = []
)

solution_project_build(
    info = info_ProjectCoreTest,
    hdrs = glob([ "Tests/**/*.h","Tests/FMT/*.h" ]),
    srcs = glob([ "Tests/**/*.h","Tests/FMT/*.h" ]) + glob([ "Tests/*.cpp", "Tests/**/*.cpp" ])
)
