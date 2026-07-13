#pragma once

#include "Math/Common.hpp"
#include "Penumbra/PShader.hpp"

class GLFWwindow;

namespace Engine {
    class Camera {
        public:
            Camera(unsigned int Width, unsigned int Height, Vector3 Position);

            void Matrix(float Fovy, float Near, float Far, Shader& shader, const char* uniform);
            void Inputs(GLFWwindow* Handle, float DT);

            Matrix4D GetViewMatrix();
            Matrix4D GetProjectionMatrix();
        private:
            Vector3 Up = Vector3UP;
            Vector3 Position;
            Vector3 Orientation = Vector3(0.0f, 0.0f, -1.0f);

            unsigned int m_Width, m_Height;
            float Fovy;

            float Speed = 10.5f;
            float Sensitivity = 100.0f;

            float Yaw = -90.0f;
            float Pitch = 0.0f;

            bool FirstClick = true;
    };
}