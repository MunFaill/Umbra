#pragma once

#include "Math/Common.hpp"
#include "Penumbra/PShader.hpp"

class GLFWwindow;

namespace Engine {
    class Camera {
        public:
            Vector3 Position;
            Vector3 Orientation = Vector3(0.0f, 0.0f, -1.0f);

            unsigned int m_Width, m_Height;
            float Fovy;

            Camera(unsigned int Width, unsigned int Height, Vector3 Position);

            void Matrix(float Fovy, float Near, float Far, Shader& shader, const char* uniform);
    };
}