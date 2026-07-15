#include "Math/Transform.hpp"

namespace Engine {
    Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) : Position(position), Rotation(rotation), Scale(scale) {}

    Matrix4D Transform::GetModelMatrix() const {
        Matrix4D translationMatrix = glm::translate(Matrix4D(1.0f), Position);

        Matrix4D rotX = Rotate(Matrix4D(1.0f), DegToRadians(Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
        Matrix4D rotY = Rotate(Matrix4D(1.0f), DegToRadians(Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
        Matrix4D rotZ = Rotate(Matrix4D(1.0f), DegToRadians(Rotation.z), Vector3(0.0f, 0.0f, 1.0f));

        Matrix4D rotationMatrix = rotY * rotX * rotZ;

        Matrix4D scaleMatrix = glm::scale(Matrix4D(1.0f), Scale);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }
}