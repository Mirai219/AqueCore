project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files { "src/**.cpp", "src/**.h" }
    includedirs { "include", "../AqueCore/include" }

    links { "AqueCore" }

    defines { "AQC_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"