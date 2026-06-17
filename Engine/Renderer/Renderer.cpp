#include "Renderer/Renderer.hpp"

float g_Vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

unsigned int g_Indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

namespace Engine {
    void Renderer::Init(GLFWwindow* Handle) {
        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        m_Vertex = VertexBuffer::Create(g_Vertices, sizeof(g_Vertices));
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        m_Shader = Shader::Create("Vertex.glsl", "Fragment.glsl");

        m_Mesh = Mesh::Create(std::move(m_Vertex), std::move(m_Index));
    }

    void Renderer::Draw() {
        m_Shader->Bind();
        m_Mesh->Bind();
        m_Context->ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        m_Context->Clear();
        m_Context->DrawInstancied(6);
        m_Mesh->Unbind();
        m_Shader->Unbind();
    }

    void Renderer::Shutdown() {
        m_Context.reset();
        m_Vertex.reset();
        m_Index.reset();
        m_Shader.reset();
        m_Mesh.reset();
    }
}