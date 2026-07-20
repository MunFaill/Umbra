#include "Platform/Windowing/Window.hpp"
#include "Tools/Event.hpp"
#include "Tools/Log.hpp"

#include <GLFW/glfw3.h>

namespace Engine {
    Window::Window(WindowProps props) : m_WindowProps(props) {
        m_WindowHandle = glfwCreateWindow(props.Width, props.Height, props.WindowTitle.c_str(), nullptr, nullptr);
        if (!m_WindowHandle) {
            Print(Error, "Unable to create a GLFW window!");
        } else {
            Print(Message,"Window initialized");
        }

        CurrentWindowProp = &m_WindowProps;
    }

    Window::~Window() {
        Print(Warning, "Window shutdown");
        Events::OnWindowResize.RemoveAllListeners();
        glfwDestroyWindow(m_WindowHandle);
    }

    void Window::HandleUpdate() {
        glfwSwapBuffers(m_WindowHandle);
        glfwPollEvents();

        int Width, Height;
        glfwGetFramebufferSize(m_WindowHandle, &Width, &Height);

        m_WindowProps.Width = static_cast<unsigned int>(Width);
        m_WindowProps.Height = static_cast<unsigned int>(Height);
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(m_WindowHandle);
    }
}