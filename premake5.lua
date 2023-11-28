
Solution.ProjectsInfo.IncludeDirs["ProjectCore"] = {
	"%{Solution.Projects.ProjectCore}/src/",
	"%{Solution.Projects.ProjectCore}/src/ProjectCore",
}

Solution.ProjectsInfo.PlatformDefineName["ProjectCore"] = "PROJECTCORE"

project "ProjectCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	Solution.HighWarnings()

	targetdir 	(Solution.Path.ProjectTargetDirectory)
	objdir 		(Solution.Path.ProjectObjectDirectory)

	files {
		"src/**.h",
		"src/**.inl",
		"src/**.cpp",
	}
	
	Solution.IncludeProject("ProjectCore")

	defines {
		"PROJECTCORE_BASE_LOGGER_NAME=\"%{Solution.Name}\""
	}

if (ProjectCoreTestsEnable)
then

Solution.Projects["ProjectCoreTests"] = Solution.Projects["ProjectCore"]

ProjectCoreTestsLaunch = {}
ProjectCoreTestsLaunch.project = "ProjectCoreTests"

Solution.Launch["ProjectCoreTests"] = ProjectCoreTestsLaunch

project "ProjectCoreTests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	Solution.HighWarnings()

	targetdir 	(Solution.Path.ProjectTargetDirectory)
	objdir 		(Solution.Path.ProjectObjectDirectory)

	files {
		"Tests/**.h",
		"Tests/**.hpp",
		"Tests/**.inl",
		"Tests/**.cpp",
	}
	
	Solution.IncludeAndLinkProject("ProjectCore")
end
	