project "Vanadium-Game"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "src/**.c", "res/**" }

   includedirs
   {
      "src",

	  -- Include Core
	  "../VanadiumEngine/src",
	  "../VanadiumEngine/src/Includes",
      "../VanadiumEngine/src/core/AssetManager",
      "../VanadiumEngine/src/core/rendering",

      -- libraries
	  "../Vendor/includes",
   }


   links
   {
        "VanadiumEngine",
        "opengl32.lib",
        "glfw3.lib"
   }

   libdirs 
   {
        "../Vendor/lib"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"