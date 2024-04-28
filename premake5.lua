
-- TODO:bazel remove Solution.Projects Infos:
Solution.Projects["ProjectCore"].PlatformDefineName = "PROJECTCORE"
Solution.Projects["ProjectCore"].Type = "StaticLib"
Solution.Projects["ProjectCore"].IncludeDirs = {
    "%{Solution.Projects.ProjectCore.Path}/src/"
}

project "ProjectCore"
    kind           (Solution.Projects["ProjectCore"].Type)
    language        "C++"
    cppdialect      "C++20"

    Solution.HighWarnings()

    targetdir      (Solution.Path.ProjectTargetDirectory)
    objdir           (Solution.Path.ProjectObjectDirectory)

    files {
         "src/**.h",
         "src/**.inl",
         "src/**.cpp",
    }
    
    Solution.Project("ProjectCore")

    defines {
         "PROJECTCORE_BASE_LOGGER_NAME=\"%{Solution.Name}\""
    }

if (ProjectCoreTestsEnable)
then

Solution.AddProject("ProjectCoreTests", Solution.Projects["ProjectCore"].Path)
Solution.Projects["ProjectCoreTests"].ProjectDependencies = {
     "ProjectCore"
}

ProjectCoreTestsLaunch = {}
ProjectCoreTestsLaunch.Project = "ProjectCoreTests"
Solution.Launch["ProjectCoreTests"] = ProjectCoreTestsLaunch

project "ProjectCoreTests"
    kind           (Solution.Projects["ProjectCoreTests"].Type)
    language      "C++"
    cppdialect      "C++20"

    Solution.HighWarnings()

    targetdir      (Solution.Path.ProjectTargetDirectory)
    objdir           (Solution.Path.ProjectObjectDirectory)

    files {
         "Tests/**.h",
         "Tests/**.hpp",
         "Tests/**.inl",
         "Tests/**.cpp",
    }

    Solution.Project("ProjectCoreTests")
end
