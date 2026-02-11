-- Container for the whole project, equivalent to .sln in VS
workspace "BorealisProject"
    -- Forces project to build for 64-bit systems
    architecture "x64"
    -- equivalent to the dropdown at the top of VS, enables or disables console, optimizations etc. per configuration 
    configurations { "Debug", "Release", "Dist" }

    -- Creates a custom variable, this is a folder path that evaluates to 
    -- something like 'Debug-windows-x64' (configuration-system-architecture) 
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- this IncludeDir is a Lua table that we use to store path variables, 
    -- includedirs used later in each project stores paths to your third-party libraries (glad, GLFW, etc.)
    -- Here we use variables (IncludeDir["variableName"]) at the top of the workspace so later in each
    -- project's includedirs {} we can use the same variable with a lua token (%{}). for example 
    -- "%{IncludeDir.GLFW}"
    -- If the path ever changes we can change the one variable instead of in each project.
    IncludeDir = {}
    IncludeDir["GLFW"] = "Borealis/vendor/GLFW/include"
    IncludeDir["glad"] = "Borealis/vendor/glad/include"
    IncludeDir["stb_image"] = "Borealis/vendor/stb_image"
    IncludeDir["spdlog"] = "Borealis/vendor/spdlog/include"

    -- 'include' tells Premake to look for other premake5.lua files inside those folders
    -- so each library can build themselves 
    include "Borealis/vendor/GLFW"
    include "Borealis/vendor/glad"

    -- The game engine project
    project "Borealis"
        location "Borealis"
        kind "staticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"
        -- This line here and in Sandbox is to satisfy spdlog which needs utf-8 encoding
        buildoptions { "/utf-8" }

        -- Where the compiled .exe and .lib files go
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        -- Where the intermediate (.obj) files go to keep your folders clean
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        -- sets up and specifies location for Precompiled Headers
        pchheader "bopch.h"
        pchsource "Borealis/src/bopch.cpp"

        -- Uses wildcards (**.cpp) to include every file of that type in the 
        -- specified folders
        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
            --"%{prj.name}/vendor/**.h",
            --"%{prj.name}/vendor/**.cpp",
        }

        -- This tells the compiler where to look when you type #include <something.h>
        -- Remember here we use some variables from the IncludeDir we created above in 
        -- workspace
        includedirs
        {
            "%{prj.name}/src",
            "%{IncludeDir.spdlog}",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.glad}",
            "%{IncludeDir.stb_image}",
        }

        -- This is the 'Linker' settings, tells the engine to pull in code from these
        -- libraries
        -- Tip: Header only libraries like stb_image do not need to be added to
        -- links, only to includedirs
        links
        {
            "GLFW",
            "glad",
            "opengl32.lib",
            "dwmapi.lib"
        }

        -- Filters only apply settings or add defines when their parameters are matched
        -- (ie. system is windows, config is debug/release/etc., )
        filter "system:windows"
            cppdialect "C++20"
            staticruntime "off"
            systemversion "latest"

            -- Defines macros so you can control code based on filters
            -- example: if (BO_PLATFORM_WINDOWS) { -run Windows specific code- }
            defines
            {
                "BO_PLATFORM_WINDOWS"
            }

          --  postbuildcommands
           -- {
           --     ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
           -- }

        filter "configurations:Debug"
            defines "BO_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "BO_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "BO_DIST"
            optimize "On"
    
    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"
        buildoptions { "/utf-8" }

        targetdir ("/bin" .. outputdir .. "/%{prj.name}")
        objdir ("/bin-int" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "%{IncludeDir.spdlog}",
            "Borealis/src"
        }

        links
        {
            "Borealis"
        }

        filter "system:windows"
                cppdialect "C++20"
                staticruntime "Off"
                systemversion "latest"

            defines
            {
                "BO_PLATFORM_WINDOWS"
            }

        filter "configurations:Debug"
            defines "BO_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "BO_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "BO_DIST"
            optimize "On"