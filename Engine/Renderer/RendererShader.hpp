#pragma once

#include <memory>
#include <string>

namespace Engine {
    class Shader {
        public:
            virtual ~Shader() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            std::unique_ptr<Shader> Create(std::string VertexShaderPath, std::string FragmentShaderPath);
    };
}