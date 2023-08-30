project "imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("build/")
	objdir ("build/obj")

	files
	{
		"*.h",
		"*.cpp",
		"backends/imgui_impl_glfw.h",
		"backends/imgui_impl_glfw.cpp",
		"backends/imgui_impl_opengl3.h",
		"backends/imgui_impl_opengl3.cpp"
	}

	includedirs
	{
		"./",
		"../glfw/include",
		"../glad/include"
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
	
	filter "configurations:Distribution"
		runtime "Release"
		optimize "Speed"
		symbols "Off"
