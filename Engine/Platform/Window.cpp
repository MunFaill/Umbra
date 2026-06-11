#include "Platform/Window.hpp"
#include <print>

#include <GLFW/glfw3.h>

namespace Engine {
    Window::Window(WindowProps props) : m_WindowProps(props) {
        m_WindowHandle = glfwCreateWindow(props.Width, props.Height, props.WindowTitle.c_str(), nullptr, nullptr);
        if (!m_WindowHandle) {
            std::print("Unable to create a GLFW window!\n");
        } else {
            std::print("Window initialized\n");
        }
    }

    Window::~Window() {
        std::print("Window shutdown\n");
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