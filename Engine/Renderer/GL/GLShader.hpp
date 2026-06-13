#pragma once

#include "Renderer/RendererShader.hpp"

namespace Engine {
    class GLShader : public Shader {
        public:
            GLShader(std::string VertexShaderPath, std::string FragmentShaderPath);
            ~GLShader() override;

            void Bind() override;
            void Unbind() override;

        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader;
            unsigned int m_ShaderProgram;

            std::string ReadFile(std::string FilePath);
    };
}