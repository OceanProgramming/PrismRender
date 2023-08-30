workspace "PrismRender"
	architecture "x64"
	configurations { "Debug", "Release", "Distribution" }
	flags { "MultiProcessorCompile" }

project "PrismRender"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("%{wks.location}/build")
	objdir ("%{wks.location}/build/obj/%{prj.name}")
	
	files
	{
		"include/**.hpp",
		"src/**.cpp",
		"%{wks.location}/vendor/glm/glm/**.hpp",
		"%{wks.location}/vendor/rapidobj/**.hpp",
		"%{wks.location}/vendor/glm/glm/**.inl"
	}
	
	includedirs
	{
		"include",
		"src",
		"%{wks.location}/vendor/glfw/include",
		"%{wks.location}/vendor/glad/include",
		"%{wks.location}/vendor/imgui",
		"%{wks.location}/vendor/imgui/backends",
		"%{wks.location}/vendor/glm",
		"%{wks.location}/vendor/rapidobj"
	}

	links
	{
		"glfw",
		"glad",
		"imgui"
	}
	
	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"
		symbols "On"
		flags { "LinkTimeOptimization" }
	
	filter "configurations:Distribution"
		runtime "Release"
		optimize "Speed"
		symbols "Off"
		flags { "LinkTimeOptimization" }

include "vendor/glfw"
include "vendor/glad"
include "vendor/imgui"