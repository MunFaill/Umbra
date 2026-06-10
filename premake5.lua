workspace "Umbra"
    configurations {"Debug", "Release"}

project "Engine"
    kind "SharedLib"
    language "C++"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/"

    files {"Engine/**.hpp", "Engine/**.cpp"}

    includedirs {"Engine/"}

    libdirs {}

    links {}
    
    filter "configurations:Debug"
		defines "Debug"
		symbols "on"
    
    filter "configurations:Release"
		defines "Release"
		optimize "on"