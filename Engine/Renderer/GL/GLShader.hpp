#pragma once

#include "Renderer/RendererShader.hpp"

namespace Engine {
    class GLShader : public Shader {
        public:
            GLShader(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
            ~GLShader() override;

            void Bind() override;
            void Unbind() override;

            void SetInt(const std::string& Name, int Value) override;
            void SetFloat(const std::string& Name, float Value) override;
            void SetVec3(const std::string& Name, const glm::vec3& Value) override;
            void SetMat4(const std::string& Name, const glm::mat4& Value) override;

        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader;
            unsigned int m_ShaderProgram;

            std::string ReadFile(std::string FilePath);
    };
}
