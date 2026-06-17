#include "Renderer/GL/GLShader.hpp"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <print>
#include <fstream>
#include <sstream>

namespace Engine{
    GLShader::GLShader(std::string VertexShaderPath, std::string FragmentShaderPath) {
        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertexCode = ReadFile(VertexShaderPath);
        std::string fragmentCode = ReadFile(FragmentShaderPath);

        const char* vertexSource = vertexCode.c_str();
        const char* fragmentSource = fragmentCode.c_str();

        glShaderSource(m_VertexShader, 1, &vertexSource, nullptr);
        glShaderSource(m_FragmentShader, 1, &fragmentSource, nullptr);

        glCompileShader(m_VertexShader);
        glCompileShader(m_FragmentShader);

        // Compile-time errors
        int success;
        char InfoLog[512];

        glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_VertexShader, 512, nullptr, InfoLog);
            std::println("Error: Vertex shader compilation failed: {}", InfoLog);
        }

        glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_FragmentShader, 512, nullptr, InfoLog);
            std::println("Error: Fragment shader compilation failed: {}", InfoLog);
        }

        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, m_VertexShader);
        glAttachShader(m_ShaderProgram, m_FragmentShader);
        glLinkProgram(m_ShaderProgram);

        glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_ShaderProgram, 512, nullptr, InfoLog);
            std::println("Error: Shader program couldn't link successfully");
        }

        std::println("Shaders files compiled and linked");
    }

    GLShader::~GLShader() {
        glDeleteProgram(m_ShaderProgram);
        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);

        std::println("Shaders and Program deleted");
    }

    void GLShader::Bind() {
        glUseProgram(m_ShaderProgram);
        std::println("Shader program binded");
    }

    void GLShader::Unbind() {
        glUseProgram(0);
        std::println("Shader program unbinded");
    }

    std::string GLShader::ReadFile(std::string FilePath) {
        std::ifstream file(FilePath);

        if (!file.is_open()) {
            std::println("Unable to open file: {}", FilePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        std::println("File readed successfully: {}", FilePath);
        return buffer.str();
    }
}