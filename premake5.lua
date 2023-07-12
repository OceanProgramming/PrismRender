workspace "Raytracing"
	architecture "x64"
	configurations { "Debug", "Release" }

project "Raytracing"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/build")
	objdir ("%{wks.location}/build/obj/%{prj.name}")
	
	files
	{
		"include/**.hpp",
		"lib/**.h",
		"src/**.cpp"
	}
	
	includedirs
	{
		"include",
		"lib",
		"src"
	}
	
	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"
		flags { "LinkTimeOptimization" }