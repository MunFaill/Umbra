#pragma once

#include "Tools/Log.hpp"

#include <GLFW/glfw3.h>

namespace Engine {
    class WindowBackend {
        public:
            inline static void Init() {
                if(!glfwInit()) {
                    Print("Error: Unable to initialize GLFW API");
                } else {
                    Print("GLFW API initialized");
                }
            }

            inline static void Shutdown() {
                glfwTerminate();
                Print("GLFW API shutdown");
            }
    };
}