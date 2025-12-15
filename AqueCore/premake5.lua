project "AqueCore"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files { "include/**.h", "src/**.cpp" }
    includedirs { "include" }

    defines { "AQC_PLATFORM_WINDOWS", "AQC_BUILD_DLL" }

    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"