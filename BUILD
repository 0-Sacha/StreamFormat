""

load("//BazelUtilities/solutions:solutions.bzl", "solution_project_build")
load(":project.bzl", "info_ProjectCore", "info_ProjectCoreTest")

solution_project_build(
    info = info_ProjectCore,
    hdrs = glob([ "src/**/*.h", "src/**/*.impl" ]),
    srcs = glob([ "src/**/*.h", "src/**/*.impl" ]) + glob([ "src/**/*.cpp" ])
)

solution_project_build(
    info = info_ProjectCoreTest,
    hdrs = glob([ "Tests/**/*.h","Tests/FMT/*.h" ]),
    srcs = glob([ "Tests/**/*.h","Tests/FMT/*.h" ]) + glob([ "Tests/*.cpp", "Tests/**/*.cpp" ])
)
