#include "Penumbra/PRenderer.hpp"
#include "Graphics/Camera.hpp"
#include "Math/Common.hpp"
#include "Tools/Asset.hpp"
#include <memory>

float g_Vertices[] = {
     -0.5f, 0.0f,  0.5f,    0.0f,  0.0f,
     -0.5f, 0.0f,  -0.5f,   5.0f,  0.0f,
     0.5f, 0.0f, -0.5f,  0.0f, 0.0f, 
     0.5f, 0.0f, 0.5f,   5.0f, 0.0f,
     0.0f, 0.8f, 0.0f,   2.5f, 5.0f
};

unsigned int g_Indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};


namespace Engine {

    void Renderer::Init(GLFWwindow* Handle, float Width, float Height) {

        m_Camera = std::make_unique<Camera>(Width, Height, Vector3(0.0f, 0.0f, 2.0f));

        // Create a context object and give it the window handle pointer
        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        // Create a vertex and index buffer for mesh
        m_Vertex = VertexBuffer::Create(g_Vertices, sizeof(g_Vertices));
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        // Create a shader and a mesh inside the asset map, and give it the data
        Assets::Shaders.Add("MainShader", Shader::Create("Engine/Assets/Base.shader"));
        Assets::Meshes.Add("Retangle", Mesh::Create(std::move(m_Vertex), std::move(m_Index)));
    }

    void Renderer::Draw() {
        Assets::Shaders.Get("MainShader").Bind();
        Assets::Meshes.Get("Retangle").Bind();

        m_Camera->Matrix(45.0f, 0.1f, 100.0f, Assets::Shaders.Get("MainShader"), "camMatrix");

        m_Context->ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        m_Context->Clear();

        m_Context->DrawIndexed(sizeof(g_Indices) / sizeof(int));
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
