#include "Graphics/Camera.hpp"
#include "Math/Common.hpp"

namespace Engine {

    Camera::Camera(unsigned int Width, unsigned int Height, Vector3 Position) : m_Width(Width), m_Height(Height), Position(Position) {}

    void Camera::Matrix(float Fovy, float Near, float Far, Shader& shader, const char* uniform) {
        Matrix4D view = LookAt(Position, Position + Orientation, Vector3UP);
        Matrix4D projection = Matrix4D(1.0f);

        projection = Perspective(Fovy, (float)m_Width / m_Height, Near, Far);
        shader.SetMat4(uniform, projection * view);
    }

}