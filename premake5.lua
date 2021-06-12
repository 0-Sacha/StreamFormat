
ProjectPublicIncludes["EngineCore"] = {
	"%{Project.EngineCore}/src/"
}

project "EngineCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
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

	IncludeAndLinkProject("CPPTools")
	IncludeProject("EngineCore")

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"