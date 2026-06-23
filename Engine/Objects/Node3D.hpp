#pragma once

#include "Objects/Node.hpp"

#include <glm/glm.hpp>

namespace Engine {
    class Node3D : public Node {
        public:
            Node3D(const std::string& NodeName) : Node(NodeName) {}
            ~Node3D() override = default;

            void Update(float DeltaTime) override;
            void Draw() override;

            glm::mat4 GetLocalTransform() const;
            glm::mat4 GetGlobalTransform() const;

            glm::vec3 Position{0.0f};
            glm::vec3 Rotation{0.0f};
            glm::vec3 Scale{1.0f};
    };
}
