workspace "Umbra"
    configurations {"Debug", "Release"}

project "Engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    targetdir "build/lib/%{cfg.buildcfg}"
    objdir "build/obj/"

    files {"Engine/**.hpp", "Engine/**.cpp"}

    includedirs {"Engine/", "Vendor/glfw/include/", "Vendor/GLAD/include"}

    libdirs {"Vendor/glfw/build/src"}

    links {"glfw3"}
    
    filter "configurations:Debug"
		defines "Debug"
		symbols "on"
    
    filter "configurations:Release"
		defines "Release"
		optimize "on"

project "Runtime"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/runtime/"

    files {"Runtime/**.hpp", "Runtime/**.cpp"}

    includedirs {"Engine/"}

    links {"Engine"}
    
    filter "configurations:Debug"
		defines "Debug"
		symbols "on"
    
    filter "configurations:Release"
		defines "Release"
		optimize "on"