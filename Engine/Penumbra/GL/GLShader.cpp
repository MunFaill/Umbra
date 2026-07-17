#include "Penumbra/GL/GLShader.hpp"
#include "Tools/Log.hpp"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <string>

namespace Engine{
    GLShader::GLShader(const std::string& ShaderPath) {
        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        ShaderSourceProgram sources = ParseShader(ShaderPath);

        const char* vertexSource = sources.VertexSource.c_str();
        const char* fragmentSource = sources.FragmentSource.c_str();

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
            Print(Error, "Vertex shader compilation failed: {}", InfoLog);
        }

        glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_FragmentShader, 512, nullptr, InfoLog);
            Print(Error, "Fragment shader compilation failed: {}", InfoLog);
        }

        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, m_VertexShader);
        glAttachShader(m_ShaderProgram, m_FragmentShader);
        glLinkProgram(m_ShaderProgram);

        glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_ShaderProgram, 512, nullptr, InfoLog);
            Print(Error, "Shader program couldn't link successfully");
        }

        Print(Message, "Shaders files compiled and linked");
    }

    GLShader::~GLShader() {
        glDeleteProgram(m_ShaderProgram);
        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);

        Print(Warning, "Shaders and Program deleted");
    }

    void GLShader::Bind() {
        glUseProgram(m_ShaderProgram);
    }

    void GLShader::Unbind() {
        glUseProgram(0);
    }

    void GLShader::SetInt(const std::string& Name, int Value) {
        glUniform1i(glGetUniformLocation(m_ShaderProgram, Name.c_str()), Value);
    }

    void GLShader::SetFloat(const std::string& Name, float Value) {
        glUniform1f(glGetUniformLocation(m_ShaderProgram, Name.c_str()), Value);
    }

    void GLShader::SetVec3(const std::string& Name, const glm::vec3& Value) {
        glUniform3fv(glGetUniformLocation(m_ShaderProgram, Name.c_str()), 1, glm::value_ptr(Value));
    }

    void GLShader::SetMat4(const std::string& Name, const glm::mat4& Value) {
        glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, Name.c_str()), 1, GL_FALSE, glm::value_ptr(Value));
    }

    ShaderSourceProgram GLShader::ParseShader(const std::string& FilePath) {
        std::ifstream file(FilePath);

        if (!file.is_open()) {
            Print(Warning, "Unable to open file: {}", FilePath);
            return { "", "" };
        }

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        bool firstLineOfShader[2] = { true, true };

        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                } else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            } else {
                if (type != ShaderType::NONE) {
                    int idx = static_cast<int>(type);
                    
                    if (firstLineOfShader[idx]) {
                        ss[idx] << line;
                        firstLineOfShader[idx] = false;
                    } else {
                        ss[idx] << '\n' << line;
                    }
                }
            }
        }

        Print(Message, "File parsed successfully: {}", FilePath);
        return { ss[0].str(), ss[1].str() };
    }
}
