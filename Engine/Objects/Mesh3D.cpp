#include "Objects/Mesh3D.hpp"
#include "Tools/AssetManager.hpp"

namespace Engine {
    void Mesh3D::Update(float DeltaTime) {
        Node::Update(DeltaTime);
    }

    void Mesh3D::Draw() {
        m_Mesh = &Assets::MeshManager.Get(MeshID);
        Node::Draw();
    }
}