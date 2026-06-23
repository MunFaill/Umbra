#include "Objects/Node3D.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
    void Node3D::Update(float DeltaTime) {
        Node::Update(DeltaTime);
    }

    void Node3D::Draw() {
        Node::Draw();
    }

    glm::mat4 Node3D::GetLocalTransform() const {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, Position);
        transform = glm::rotate(transform, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, Scale);
        return transform;
    }

    glm::mat4 Node3D::GetGlobalTransform() const {
        glm::mat4 global = GetLocalTransform();

        if (auto parent = GetParent()) {
            if (auto parent3D = std::dynamic_pointer_cast<Node3D>(parent)) {
                global = parent3D->GetGlobalTransform() * global;
            }
        }

        return global;
    }
}
