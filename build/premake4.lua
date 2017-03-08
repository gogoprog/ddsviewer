solution "ddsviewer"
    configurations { "Debug", "Release" }

    project "ddsviewer"
        kind "ConsoleApp"
        language "C++"
        files { "../src/**.h", "../src/**.cpp" }
        links { "sfml-graphics", "sfml-window", "sfml-system" }

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }
