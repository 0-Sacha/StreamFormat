
ProjectPublicIncludes["EngineCore"] = {
	"%{Project.EngineCore}/src/",
	"%{Project.EngineCore}/src/EngineCore/LIB",
	"%{Project.EngineCore}/src/EngineCore/Instrumentation",
	"%{Project.EngineCore}/src/EngineCore/TNX",
	"%{Project.EngineCore}/src/EngineCore/Test",
	"%{Project.EngineCore}/src/EngineCore/Core",
}

project "EngineCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	pchheader "EngineCorepch.h"
	pchsource "src/EngineCore/Core/EngineCorepch.cpp"

	targetdir 	(project_targetdir .. "/%{prj.name}")
	objdir 		(project_objdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.inl",
		"src/**.cpp",
	}

	IncludeProject("EngineCore")

	defines {
		"ENGINECORE_BASE_LOGGER_NAME=\"%{ProjectName}\""
	}