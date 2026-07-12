#include "Penumbra/PRenderer.hpp"
#include "Graphics/Camera.hpp"
#include "Math/Common.hpp"
#include "Tools/Asset.hpp"

#include <vector>
#include <memory>

std::vector<Engine::Vertex> g_Vertices = {

    { // Vertex 0
        { -0.5f, -0.5f, 0.0f }, // Position
        {  1.0f,  0.0f, 0.0f, 1.0f }, // Colors
        {  0.0f,  0.0f }, // UV
        {  0.0f,  0.0f, 1.0f } // Normal
    },

    { 
        {  0.5f, -0.5f, 0.0f },
        {  0.0f,  1.0f, 0.0f, 1.0f },
        {  1.0f,  0.0f },
        {  0.0f,  0.0f, 1.0f }
    },

    { 
        {  0.0f,  0.5f, 0.0f },
        {  0.0f,  0.0f, 1.0f, 1.0f },
        {  0.5f,  1.0f },
        {  0.0f,  0.0f, 1.0f }
    }
};

unsigned int g_Indices[] = {
    0, 1, 2
};

namespace Engine {

    void Renderer::Init(GLFWwindow* Handle, float Width, float Height) {

        m_Camera = std::make_unique<Camera>(Width, Height, Vector3(0.0f, 0.0f, 2.0f));

        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        uint32_t vertexBufferSize = g_Vertices.size() * sizeof(Engine::Vertex);
        m_Vertex = VertexBuffer::Create(g_Vertices.data(), vertexBufferSize);
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        Assets::Shaders.Add("MainShader", Shader::Create("Engine/Assets/Base.shader"));
        Assets::Meshes.Add("Retangle", Mesh::Create(std::move(m_Vertex), std::move(m_Index)));
    }

    void Renderer::Draw() {
        m_Context->ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        m_Context->Clear();

        Assets::Shaders.Get("MainShader").Bind();
        Assets::Meshes.Get("Retangle").Bind();

        m_Camera->Matrix(45.0f, 0.1f, 100.0f, Assets::Shaders.Get("MainShader"), "camMatrix");

        m_Context->DrawIndexed(sizeof(g_Indices) / sizeof(unsigned int));

        Assets::Meshes.Get("Retangle").Unbind();
        Assets::Shaders.Get("MainShader").Unbind();
    }

    void Renderer::Shutdown() {
        m_Context.reset();
        m_Vertex.reset();
        m_Index.reset();
        m_Camera.reset();
    }
}
