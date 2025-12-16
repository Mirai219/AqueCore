workspace "AqueEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDirs = {};
    IncludeDirs["spdlog"] = "AqueCore/vendor/spdlog/include"

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
    }

    defines 
    { 
        "AQC_PLATFORM_WINDOWS",
        "AQC_BUILD_DLL",
        "SPDLOG_HEADER_ONLY"
    }

    filter "system:windows"
        buildoptions { "/utf-8" }

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
        "AqueCore" 
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