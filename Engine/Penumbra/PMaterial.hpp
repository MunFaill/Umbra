#pragma once

#include "Math/Common.hpp"
#include <string>

namespace Engine {
    struct Material {
        Vector4 Albedo = Vector4(1.0f);
        float Specular = 0.5f;
        int Shininess = 256;
        std::string TextureID = "DebugTexture";
    };
}