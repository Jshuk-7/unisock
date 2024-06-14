workspace "unisock"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "testbed"
    
    -- Workspace wide build options for MSVC
    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
    include "unisock/build-unisock.lua"
group ""

include "testbed/build-testbed.lua"