project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "On"

	targetdir ("build/")
	objdir ("build/obj")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}
	
	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS"
		}

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
	
