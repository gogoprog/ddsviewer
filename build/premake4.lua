solution "ddsviewer"
    configurations { "Debug", "Release" }

    project "ddsviewer"
        kind "ConsoleApp"
        language "C++"
        files { "../src/**.h", "../src/**.cpp" }
        links { "sfml-graphics", "sfml-window", "sfml-system", "GL" }

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }
            targetsuffix "d"

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }
