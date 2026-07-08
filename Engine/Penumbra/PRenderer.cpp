#include "Penumbra/PRenderer.hpp"
#include "Tools/Asset.hpp"

#include <glm/gtc/matrix_transform.hpp>

float g_Vertices[] = {
     -0.5f, -0.5f, +0.0f, +0.0f,
     +0.5f, -0.5f, +1.0f, +0.0f,
     +0.5f, +0.5f, +1.0f, +1.0f,
     -0.5f, +0.5f, +0.0f, +1.0f
};

unsigned int g_Indices[] = {
    0, 1, 3,
    1, 2, 3
};

namespace Engine {

    void Renderer::Init(GLFWwindow* Handle, float Width, float Height) {

        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        m_Vertex = VertexBuffer::Create(g_Vertices, sizeof(g_Vertices));
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        Assets::Shaders.Add("MainShader", Shader::Create("Engine/Assets/Vertex.glsl", "Engine/Assets/Fragment.glsl"));
        Assets::Meshes.Add("Retangle", Mesh::Create(std::move(m_Vertex), std::move(m_Index)));
    }

    void Renderer::Draw() {
        Assets::Shaders.Get("MainShader").Bind();
        Assets::Meshes.Get("Retangle").Bind();

        m_Context->ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        m_Context->Clear();

        m_Context->DrawIndexed(6);
        Assets::Meshes.Get("Retangle").Unbind();
        Assets::Shaders.Get("MainShader").Unbind();
    }


    void Renderer::Shutdown() {
        m_Context.reset();
        m_Vertex.reset();
        m_Index.reset();
    }
}
