-- premake5.lua
workspace "Vanadium"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "VanadiumUi"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

   filter "action:vs*"
      buildoptions { "/MP" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "VanadiumEngine/Build-VanadiumEngine.lua"

-- include "VanadiumGame/Build-VanadiumGame.lua"

include "VanadiumUi/Build-VanadiumUi.lua"

-- include "CirclePhysics/Build-CirclePhysics.lua"