// SoPhIsTiCaTeD

#pragma once

#include <print>
#include <GLFW/glfw3.h>

namespace Engine {
    class WindowBackend {
        public:
            inline static void Init() {
                if(!glfwInit()) {
                    std::println("Error: Unable to initialize GLFW API");
                } else {
                    std::println("GLFW API initialized");
                }
            }

            inline static void Shutdown() {
                glfwTerminate();
                std::println("GLFW API shutdown");
            }
    };
}