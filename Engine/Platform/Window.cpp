#include "Platform/Window.hpp"
#include "Tools/Event.hpp"

#include <print>
#include <GLFW/glfw3.h>

namespace Engine {
    Window::Window(WindowProps props) : m_WindowProps(props) {
        m_WindowHandle = glfwCreateWindow(props.Width, props.Height, props.WindowTitle.c_str(), nullptr, nullptr);
        if (!m_WindowHandle) {
            std::println("Unable to create a GLFW window!");
        } else {
            std::println("Window initialized");
        }
    }

    Window::~Window() {
        std::println("Window shutdown");
        Events::OnWindowResize.RemoveAllListeners();
        glfwDestroyWindow(m_WindowHandle);
    }

    void Window::HandleUpdate() {
        glfwSwapBuffers(m_WindowHandle);
        glfwPollEvents();
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(m_WindowHandle);
    }
}