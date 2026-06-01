solution "ddsviewer"
    configurations { "Debug", "Release" }

    project "ddsviewer"
        kind "ConsoleApp"
        language "C++"
        files { "../src/**.h", "../src/**.cpp" }
        links { "sfml-graphics", "sfml-window", "sfml-system", "GL" }

        filter { "configurations:Debug" }
            defines { "DEBUG" }
            symbols "On"
            targetsuffix "d"

        filter { "configurations:Release" }
            defines { "NDEBUG" }
            optimize "On"
