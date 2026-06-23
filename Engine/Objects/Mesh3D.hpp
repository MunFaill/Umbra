#pragma once

#include "Objects/Node3D.hpp"
#include "Renderer/RendererMesh.hpp"
#include <string>

namespace Engine {
    class Mesh3D : public Node3D {
        protected:
            std::string MeshID;
        public:
            Mesh3D(const std::string& NodeName, const std::string& MeshID) : Node3D(NodeName), MeshID(MeshID) {}
            ~Mesh3D() override = default;

            void Update(float DeltaTime) override;
            void Draw() override;
        private:
            Mesh* m_Mesh;
    };
}