// SoPhIsTiCaTeD

#pragma once

#include <print>
#include <GLFW/glfw3.h>

namespace Engine {
    class WindowBackend {
        public:
            static void Init() {if(!glfwInit()){std::print("Error: Unable to initialize GLFW API\n");} else {std::print("GLFW API initialized\n");}}
            static void Shutdown() {glfwTerminate(); std::print("GLFW API shutdown\n");}
    };
}