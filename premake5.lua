workspace "TEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
--IncludeDir = {}
--IncludeDir["GLFW"] = "TEngine/vendor/GLFW/include"
project "TEngine"
	location "TEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   libdirs {
      "Dependencies/DirectX/Lib"
   }
   
   --rules{
   --   include "Dependencies/DirectX/Lib"
   --}

	pchheader "precompiled.h"
	pchsource "precompiled.cpp"

   forceincludes {
      "precompiled.h"
   }

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
      ".",
		"%{prj.name}/src",
		"%{prj.name}/src/core",
		"Dependencies/DirectX/Include"
		--"%{IncludeDir.GLFW}"
	}
   
   include "Dependencies/DirectX/Lib"

	links 
	{ 
		--"GLFW",
		--"opengl32.lib"

	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TENGINE_PLATFORM=TENGINE_PLATFORM_WINDOWS",
			"TENGINE_LIBRARY"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
      buildoptions "/MDd"

	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
      buildoptions "/MD"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

   include "Dependencies/DirectX/Lib"

	includedirs
	{
		"Dependencies/DirectX/Include",
		"TEngine/src"
	}

	links
	{
		"TEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TENGINE_PLATFORM=TENGINE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
      buildoptions "/MDd"

	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
      buildoptions "/MD"
