
Solution.ProjectsInfo.Includes["EngineCore"] = {
	"%{Solution.Projects.EngineCore}/src/",
	"%{Solution.Projects.EngineCore}/src/EngineCore",
}

project "EngineCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir 	(Solution.Path.ProjectTargetDirectory)
	objdir 		(Solution.Path.ProjectObjectDirectory)

	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.inl",
		"src/**.cpp",
	}
	
	Solution.IncludeProject("EngineCore")

	defines {
		"ENGINECORE_BASE_LOGGER_NAME=\"%{Solution.Name}\""
	}

project "EngineCoreTests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir 	(Solution.Path.ProjectTargetDirectory)
	objdir 		(Solution.Path.ProjectObjectDirectory)

	files {
		"Tests/**.h",
		"Tests/**.hpp",
		"Tests/**.inl",
		"Tests/**.cpp",
	}
	
	Solution.IncludeAndLinkProject("EngineCore")
	