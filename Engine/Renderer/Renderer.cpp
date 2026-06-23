#include "Renderer/Renderer.hpp"
#include "Objects/Node3D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

float g_Vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

unsigned int g_Indices[] = {
    0, 1, 3,
    1, 2, 3
};

namespace Engine {
    static std::vector<unsigned char> CreateCheckerboardTexture(unsigned int Size) {
        std::vector<unsigned char> pixels(Size * Size * 4);

        for (unsigned int y = 0; y < Size; ++y) {
            for (unsigned int x = 0; x < Size; ++x) {
                bool light = ((x / 8) + (y / 8)) % 2 == 0;
                unsigned int index = (y * Size + x) * 4;

                pixels[index + 0] = light ? 255 : 64;
                pixels[index + 1] = light ? 255 : 64;
                pixels[index + 2] = light ? 255 : 64;
                pixels[index + 3] = 255;
            }
        }

        return pixels;
    }

    void Renderer::Init(GLFWwindow* Handle, float Width, float Height) {
        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        m_Vertex = VertexBuffer::Create(g_Vertices, sizeof(g_Vertices));
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        m_Shader = Shader::Create("Engine/Assets/Vertex.glsl", "Engine/Assets/Fragment.glsl");

        m_Mesh = Mesh::Create(std::move(m_Vertex), std::move(m_Index));

        auto checkerboard = CreateCheckerboardTexture(64);
        m_Texture = Texture::Create(64, 64, checkerboard.data());

        m_Projection = glm::perspective(glm::radians(45.0f), Width / Height, 0.1f, 100.0f);
        m_View = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void Renderer::Draw(Node3D* SceneRoot) {
        glm::mat4 model(1.0f);
        if (SceneRoot) {
            model = SceneRoot->GetGlobalTransform();
        }

        m_Shader->Bind();
        m_Shader->SetMat4("u_Model", model);
        m_Shader->SetMat4("u_View", m_View);
        m_Shader->SetMat4("u_Projection", m_Projection);

        m_Texture->Bind();
        m_Mesh->Bind();
        m_Context->ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        m_Context->Clear();
        m_Context->DrawInstancied(6);
        m_Mesh->Unbind();
        m_Texture->Unbind();
        m_Shader->Unbind();
    }

    void Renderer::Shutdown() {
        m_Context.reset();
        m_Vertex.reset();
        m_Index.reset();
        m_Shader.reset();
        m_Mesh.reset();
        m_Texture.reset();
    }
}
