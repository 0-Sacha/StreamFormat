
ProjectPublicIncludes["EngineCore"] = {
	"%{Project.EngineCore}/src/"
}

project "EngineCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	pchheader "EngineCorepch.h"
	pchsource "src/EngineCorepch.cpp"

	targetdir 	("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir 		("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.hpp",
		"src/**.inl",
		"src/**.cpp",
	}

	IncludeProject("EngineCore")

	defines {
		"ENGINE_CORE_BASE_LOGGER_NAME=\"%{ProjectName}\""
	}