"Wait for Bazelv8 for a more convenient way; this should not exist"

load("@BazelUtilities//solutions:solutions.bzl", "solution_project_info", "ProjectType")

# buildifier: disable=name-conventions
info_ProjectCore = solution_project_info(
    name = "ProjectCore",
    project_type = ProjectType.StaticLib,
    include_dirs = [ "src/", "src/ProjectCore" ],
    platform_define_name = "PROJECTCORE",
    copts = [ "-std=c++20" ],
    linkopts = []
)
