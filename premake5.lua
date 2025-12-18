workspace "AqueEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDirs = {};
    IncludeDirs["spdlog"] = "AqueCore/vendor/spdlog/include"
    IncludeDirs["glfw"] = "AqueCore/vendor/glfw/include"
    IncludeDirs["glad"] = "AqueCore/vendor/glad/include"
    IncludeDirs["imgui"] = "AqueCore/vendor/imgui"

project "AqueCore"
    kind "SharedLib"
    location "AqueCore"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/include/**.h", 
        "%{prj.name}/src/**.cpp" 
    }

    includedirs 
    { 
        "%{prj.name}/include",
        IncludeDirs["spdlog"],
        IncludeDirs["glfw"],
        IncludeDirs["glad"],
        IncludeDirs["imgui"],
    }

    defines 
    { 
        "AQC_PLATFORM_WINDOWS",
        "AQC_BUILD_DLL",
        "SPDLOG_HEADER_ONLY",
        "GLFW_INCLUDE_NONE",
        "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
    }

    links
    {
        "glfw",
        "opengl32.lib",
        "glad",
        "imgui"
    }

    filter "system:windows"
        buildoptions { "/utf-8" }
        postbuildcommands
        {
            "{COPY} %{cfg.buildtarget.abspath} %{wks.location}/bin/" .. outputdir .. "/Sandbox"
        }

    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"

project "Sandbox"
    kind "ConsoleApp"
    location "Sandbox"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h" 
    }

    includedirs 
    { 
        "AqueCore/include",
        IncludeDirs["spdlog"],
    }

    links 
    { 
        "AqueCore",
    }

    defines 
    { 
        "AQC_PLATFORM_WINDOWS",
    }

    filter "system:windows"
        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"

project "glfw"
    kind "StaticLib"
    location "AqueCore/vendor/glfw"
    language "C"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"AqueCore/vendor/glfw/include/GLFW/glfw3.h",
		"AqueCore/vendor/glfw/include/GLFW/glfw3native.h",
		"AqueCore/vendor/glfw/src/glfw_config.h",
		"AqueCore/vendor/glfw/src/context.c",
		"AqueCore/vendor/glfw/src/init.c",
		"AqueCore/vendor/glfw/src/input.c",
		"AqueCore/vendor/glfw/src/monitor.c",

		"AqueCore/vendor/glfw/src/null_init.c",
		"AqueCore/vendor/glfw/src/null_joystick.c",
		"AqueCore/vendor/glfw/src/null_monitor.c",
		"AqueCore/vendor/glfw/src/null_window.c",

		"AqueCore/vendor/glfw/src/platform.c",
		"AqueCore/vendor/glfw/src/vulkan.c",
		"AqueCore/vendor/glfw/src/window.c",
	}

    includedirs
    {
        "AqueCore/vendor/glfw/include"
    }

    filter "system:windows"
		systemversion "latest"

		files
		{
			"AqueCore/vendor/glfw/src/win32_init.c",
			"AqueCore/vendor/glfw/src/win32_joystick.c",
			"AqueCore/vendor/glfw/src/win32_module.c",
			"AqueCore/vendor/glfw/src/win32_monitor.c",
			"AqueCore/vendor/glfw/src/win32_time.c",
			"AqueCore/vendor/glfw/src/win32_thread.c",
			"AqueCore/vendor/glfw/src/win32_window.c",
			"AqueCore/vendor/glfw/src/wgl_context.c",
			"AqueCore/vendor/glfw/src/egl_context.c",
			"AqueCore/vendor/glfw/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
		}
    
    filter "configurations:Debug"
	runtime "Debug"
	symbols "on"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		symbols "on"
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
        symbols "off"

project "glad"
    kind "StaticLib"
    location "AqueCore/vendor/glad"
    language "C"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"AqueCore/vendor/glad/src/glad.c"
	}

    includedirs
    {
        IncludeDirs["glad"]
    }

    filter "system:windows"
		buildoptions { "/utf-8" }

project "imgui"
    kind "StaticLib"
    location "AqueCore/vendor/imgui"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"AqueCore/vendor/imgui/*.cpp",
        "AqueCore/vendor/imgui/*.h",
	}

    filter "system:windows"
		buildoptions { "/utf-8" }