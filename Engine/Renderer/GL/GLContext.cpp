#include "Renderer/GL/GLContext.hpp"

#include <print>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Engine {
    GLContext::GLContext() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        std::print("GLFW context created\n");
    }

    GLContext::~GLContext() {
        std::print("GL context shutdown\n");
    }

    void GLContext::Init(GLFWwindow* Handle) {
        glfwMakeContextCurrent(Handle);
        gladLoadGL(glfwGetProcAddress);
        std::print("GL context created\n");
    }

    void GLContext::ClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void GLContext::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}