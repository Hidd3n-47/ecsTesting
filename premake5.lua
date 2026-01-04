workspace "ecsTesting"
architecture "x64"

configurations
{
    "Dev",
    "Release"
}

outputName          = "%{cfg.buildcfg}"
outputPath          = "$(SolutionDir)scratch/bin/" .. outputName .. "/"
outputIntPath       = "$(SolutionDir)scratch/bin-int/" .. outputName .. "/"

include "ecsTestingProject/"
