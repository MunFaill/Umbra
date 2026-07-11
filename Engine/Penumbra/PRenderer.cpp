#include "Penumbra/PRenderer.hpp"
#include "Tools/Asset.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float g_Vertices[] = {
     -0.5f, -0.5f, +0.0f, +0.0f,
     +0.5f, -0.5f, +1.0f, +0.0f,
     +0.5f, +0.5f, +1.0f, +1.0f,
     -0.5f, +0.5f, +0.0f, +1.0f
};

unsigned int g_Indices[] = {
    0, 1, 2,
    2, 3, 0
};

namespace Engine {

    void Renderer::Init(GLFWwindow* Handle, float Width, float Height) {

        // Create a context object and give it the window handle pointer
        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        // Create a vertex and index buffer for mesh
        m_Vertex = VertexBuffer::Create(g_Vertices, sizeof(g_Vertices));
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        // Set up a 4:3 projection
        glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); // 4:3 ortho projection

        // Create a shader and a mesh inside the asset map, and give it the data
        Assets::Shaders.Add("MainShader", Shader::Create("Engine/Assets/Base.shader"));
        Assets::Meshes.Add("Retangle", Mesh::Create(std::move(m_Vertex), std::move(m_Index)));

        // Shader configuration stuff, bind, modify and unbind
        Assets::Shaders.Get("MainShader").Bind();
            Assets::Shaders.Get("MainShader").SetMat4("u_MVP", projection);
        Assets::Shaders.Get("MainShader").Unbind();
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
