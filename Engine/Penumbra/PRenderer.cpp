#include "Penumbra/PRenderer.hpp"
#include "Tools/Asset.hpp"
#include "Math/Common.hpp"

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

        // Create a context object and give it the window handle pointer
        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        // Create a vertex and index buffer for mesh
        m_Vertex = VertexBuffer::Create(g_Vertices, sizeof(g_Vertices));
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        // Projections, view coords and projection coords
        Matrix4D model = Matrix4D(1.0f);
        Matrix4D view = Matrix4D(1.0f);
        Matrix4D projection = Matrix4D(1.0f);

        view = Transform(view, Vector3(0.0f, -0.5f, -2.0f));
        projection = glm::perspective(glm::radians(75.0f), (float)(Width / Height), 0.1f, 100.0f);

        // Create a shader and a mesh inside the asset map, and give it the data
        Assets::Shaders.Add("MainShader", Shader::Create("Engine/Assets/Base.shader"));
        Assets::Meshes.Add("Retangle", Mesh::Create(std::move(m_Vertex), std::move(m_Index)));

        // Shader configuration stuff, bind, modify and unbind
        Assets::Shaders.Get("MainShader").Bind();
            Assets::Shaders.Get("MainShader").SetMat4("model", model);
            Assets::Shaders.Get("MainShader").SetMat4("view", view);
            Assets::Shaders.Get("MainShader").SetMat4("proj", projection);
        Assets::Shaders.Get("MainShader").Unbind();
    }

    void Renderer::Draw() {
        Assets::Shaders.Get("MainShader").Bind();
        Assets::Meshes.Get("Retangle").Bind();

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
    }
}
