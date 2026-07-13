#include "Graphics/Camera.hpp"
#include "Math/Common.hpp"
#include "Tools/Log.hpp"

#include <GLFW/glfw3.h>

namespace Engine {

    Camera::Camera(unsigned int Width, unsigned int Height, Vector3 Position) : m_Width(Width), m_Height(Height), Position(Position) {}

    void Camera::Matrix(float Fovy, float Near, float Far, Shader& shader, const char* uniform) {
        Matrix4D view = LookAt(Position, Position + Orientation, Up);
        Matrix4D projection = Matrix4D(1.0f);

        projection = Perspective(Fovy, (float)m_Width / m_Height, Near, Far);
        shader.SetMat4(uniform, projection * view);

        Print("Camera initialized","");
    }

    void Camera::Inputs(GLFWwindow* window, float deltaTime) {
        // TODO: Use a built-in input system

        float velocity = Speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            Position += velocity * Orientation;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Position -= velocity * Orientation;

        Vector3 rightDirection = glm::normalize(glm::cross(Orientation, Vector3UP));
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Position -= velocity * rightDirection;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Position += velocity * rightDirection;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            Position += velocity * Vector3UP;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            Position += velocity * Vector3Down;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            if (FirstClick) {
                mouseX = m_Width / 2.0;
                mouseY = m_Height / 2.0;
                glfwSetCursorPos(window, m_Width / 2.0, m_Height / 2.0);
                FirstClick = false;
            }

            float rotX = (float)(mouseX - (m_Width / 2.0f)) / m_Width;
            float rotY = (float)(mouseY - (m_Height / 2.0f)) / m_Height;

            Yaw += rotX * Sensitivity;
            Pitch += -rotY * Sensitivity;

            if (Pitch > 89.0f) Pitch = 89.0f;
            if (Pitch < -89.0f) Pitch = -89.0f;

            Vector3 direction;
            direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            direction.y = sin(glm::radians(Pitch));
            direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Orientation = glm::normalize(direction);

            Vector3 right = glm::normalize(glm::cross(Orientation, Vector3UP));
            Up = glm::normalize(glm::cross(right, Orientation));

            glfwSetCursorPos(window, m_Width / 2.0f, m_Height / 2.0f);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            FirstClick = true;
        }
    }

    Matrix4D Camera::GetViewMatrix() {
        return LookAt(Position, Position + Orientation, Up);
    }

    Matrix4D Camera::GetProjectionMatrix() {
        return Perspective(Fovy, (float)m_Width / m_Height, 0.1f, 100.0f); // Guarde o Fovy na classe!
    }

}