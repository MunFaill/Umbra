#include "Penumbra/PRenderer.hpp"
#include "Objects/Model3D.hpp"
#include "Objects/ObjectTree.hpp"

#include <memory>

namespace Engine {
    void Renderer::Init(GLFWwindow* Handle) {

        m_Context = RendererContext::Create();
        m_Context->Init(Handle);;
    }

    void Renderer::Draw(unsigned int Widht, unsigned int Height) {

        m_Context->ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        m_Context->Clear();

        for (auto& obj : GameObjects) {

            if (Camera3D* cameraOBJ = dynamic_cast<Camera3D*>(obj.get())) { // Cameras
                cameraOBJ->Render("MainShader", Widht, Height);
            }

            if (Mesh3D* meshOBJ = dynamic_cast<Mesh3D*>(obj.get())) { // Meshes
                meshOBJ->Render(m_Context.get());
            }

            if (Model3D* modelOBJ = dynamic_cast<Model3D*>(obj.get())) {
                modelOBJ->Render(m_Context.get());
            }
        }
    }

    void Renderer::Shutdown() {
        m_Context.reset();
        m_Vertex.reset();
        m_Index.reset();
        ClearTree();
    }

}
