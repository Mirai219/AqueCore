workspace "AquaEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "AqueCore/premake5.lua"
    include "Sandbox/premake5.lua"
