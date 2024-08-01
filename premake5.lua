
-- TODO:bazel remove Solution.Projects Infos:
Solution.Projects["StreamFormat"].PlatformDefineName = "STREAMFORMAT"
Solution.Projects["StreamFormat"].Type = "StaticLib"
Solution.Projects["StreamFormat"].IncludeDirs = {
    "%{Solution.Projects.StreamFormat.Path}/src/"
}

project "StreamFormat"
    kind           (Solution.Projects["StreamFormat"].Type)
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
    
    Solution.Project("StreamFormat")

    defines {
         "STREAMFORMAT_BASE_LOGGER_NAME=\"%{Solution.Name}\""
    }

if (StreamFormatTestsEnable)
then

Solution.AddProject("StreamFormatTests", Solution.Projects["StreamFormat"].Path)
Solution.Projects["StreamFormatTests"].ProjectDependencies = {
     "StreamFormat"
}

StreamFormatTestsLaunch = {}
StreamFormatTestsLaunch.Project = "StreamFormatTests"
Solution.Launch["StreamFormatTests"] = StreamFormatTestsLaunch

project "StreamFormatTests"
    kind           (Solution.Projects["StreamFormatTests"].Type)
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

    Solution.Project("StreamFormatTests")
end
