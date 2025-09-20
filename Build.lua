-- premake5.lua
workspace "Vanadium"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "VanadiumGame"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "VanadiumEngine"
include "VanadiumEngine/Build-VanadiumEngine.lua"
group ""

include "VanadiumGame/Build-VanadiumGame.lua"