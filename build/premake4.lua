solution "ddsviewer"
    configurations { "Debug", "Release" }

    project "ddsviewer"
        kind "ConsoleApp"
        language "C++"
        files { "../src/**.h", "../src/**.cpp" }

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }
