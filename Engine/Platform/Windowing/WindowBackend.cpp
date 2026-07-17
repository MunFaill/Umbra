#include "Platform/Windowing/WindowBackend.hpp"

#include "Tools/Log.hpp"

#include <GLFW/glfw3.h>

namespace Engine {
    void WindowBackend::Initialize() {
        if (!glfwInit()) {
            Print(Error, "GLFW backend could not be initialized");
        } else {
            Print(Message, "GLFW backend initialized successfully");
        }
    }

    void WindowBackend::Shutdown() {
        glfwTerminate();
        Print(Warning, "GLFW backend shutdown");
    }
}