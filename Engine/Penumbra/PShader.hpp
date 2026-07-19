#pragma once

#include <memory>
#include <string>

#include "Math/Common.hpp"

namespace Engine {
    class Shader {
        public:
            virtual ~Shader() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual void SetInt(const std::string& Name, int Value) = 0;
            virtual void SetFloat(const std::string& Name, float Value) = 0;
            virtual void SetVec3(const std::string& Name, const Vector3& Value) = 0;
            virtual void SetVec4(const std::string& Name, const Vector4& Value) = 0;
            virtual void SetMat4(const std::string& Name, const glm::mat4& Value) = 0;

            static std::unique_ptr<Shader> Create(const std::string& ShaderPath);
    };
}
