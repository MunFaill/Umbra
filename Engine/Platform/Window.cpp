#include "Platform/Window.hpp"
#include "Tools/Event.hpp"
#include "Tools/Log.hpp"

#include <GLFW/glfw3.h>

namespace Engine {
    Window::Window(WindowProps props) : m_WindowProps(props) {
        m_WindowHandle = glfwCreateWindow(props.Width, props.Height, props.WindowTitle.c_str(), nullptr, nullptr);
        if (!m_WindowHandle) {
            Print("Unable to create a GLFW window!");
        } else {
            Print("Window initialized");
        }
    }

    Window::~Window() {
        Print("Window shutdown");
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