#include "Penumbra/GL/GLContext.hpp"
#include "Tools/Event.hpp"
#include "Tools/Log.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Engine {

    void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        Events::OnWindowResize.Invoke(width, height);
    }

    GLContext::GLContext() { // Initialize GL context, using OpenGL 4.6 Core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #if defined (__APPLE__)
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) // For MACOS
        #endif
        Print(Message, "GL context created");
    }

    GLContext::~GLContext() {
        Print(Warning, "GL context shutdown");
    }

    void GLContext::Init(GLFWwindow* Handle) {
        glfwMakeContextCurrent(Handle);

        gladLoadGL(glfwGetProcAddress);

        glfwSetFramebufferSizeCallback(Handle, FrameBufferSizeCallback);

        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha func

        Print(Message, "GL context initialized");
    }

    void GLContext::ClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void GLContext::DrawIndexed(unsigned int Size) {
        glDrawElements(GL_TRIANGLES, Size, GL_UNSIGNED_INT, 0);
    }

    void GLContext::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}