-- ---------------------------- ecsTesting Project.
project "ecsTesting"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    staticruntime "Off"
    cppdialect "C++20"

    targetdir(outputPath .. "%{prj.name}")
    objdir(outputIntPath .. "%{prj.name}")

    pchheader "ecsTestingPch.h"
    pchsource "%{prj.name}/src/ecsTestingPch.cpp"

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/",
        "%{prj.name}/Src/",

        "$(SolutionDir)deps/Include/",
    }

    libdirs
    {
        "$(SolutionDir)deps/Lib/",
    }

    links
    {
        "SDL3.lib"
    }

    postbuildcommands
    {
        ("{COPYFILE} %[$(SolutionDir)deps/Lib/SDL3.dll] %[" .. outputPath .. "ecsTesting/]"),
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Dev"
        runtime "Debug"
        defines "DEV_CONFIGURATION"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
