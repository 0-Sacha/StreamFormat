
Solution.ProjectsInfo.Includes["EngineCore"] = {
	"%{Solution.Projects.EngineCore}/src/",
	"%{Solution.Projects.EngineCore}/src/EngineCore",
	"%{Solution.Projects.EngineCore}/src/EngineCore/Core",
	"%{Solution.Projects.EngineCore}/src/EngineCore/LIB",
	"%{Solution.Projects.EngineCore}/src/EngineCore/TNX",
	"%{Solution.Projects.EngineCore}/src/EngineCore/Test"
}

project "EngineCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	pchheader "EngineCorepch.h"
	pchsource "src/EngineCore/Core/EngineCorepch.cpp"

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