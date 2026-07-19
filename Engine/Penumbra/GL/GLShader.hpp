#pragma once

#include "Penumbra/PShader.hpp"

namespace Engine {
    struct ShaderSourceProgram {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class GLShader : public Shader {
        public:
            GLShader(const std::string& ShaderPath);
            ~GLShader() override;

            void Bind() override;
            void Unbind() override;

            void SetInt(const std::string& Name, int Value) override;
            void SetFloat(const std::string& Name, float Value) override;
            void SetVec3(const std::string& Name, const glm::vec3& Value) override;
            void SetVec4(const std::string& Name, const Vector4& Value) override;
            void SetMat4(const std::string& Name, const glm::mat4& Value) override;

        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader;
            unsigned int m_ShaderProgram;

            ShaderSourceProgram ParseShader(const std::string& FilePath);
    };
}
