#include "Penumbra/PRenderer.hpp"
#include "Graphics/Camera.hpp"
#include "Math/Common.hpp"
#include "Math/Time.hpp"
#include "Math/Transform.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Mesh3D.hpp"
#include "Penumbra/PTexture.hpp"
#include "Tools/Asset.hpp"
#include "Objects/ObjectTree.hpp"

#include <vector>
#include <memory>

std::vector<Engine::Vertex> g_Vertices = {
    // Position: { X, Y, Z }, Color: { R, G, B, A }, UV: { U, V }, Normal: { X, Y, Z }

    { { -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f,  1.0f } }, // 0
    { {  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f,  1.0f } }, // 1
    { {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f } }, // 2
    { { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f,  1.0f } }, // 3

    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } }, // 4
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } }, // 5
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } }, // 6
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } }, // 7

    { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }, // 8
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } }, // 9
    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } }, // 10
    { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } }, // 11

    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }, {  1.0f, 0.0f, 0.0f } }, // 12
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }, {  1.0f, 0.0f, 0.0f } }, // 13
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f } }, // 14
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, {  1.0f, 0.0f, 0.0f } }, // 15

    { { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f,  1.0f, 0.0f } }, // 16
    { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f,  1.0f, 0.0f } }, // 17
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f,  1.0f, 0.0f } }, // 18
    { { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f,  1.0f, 0.0f } }, // 19

    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.5f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } }, // 20
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.5f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } }, // 21
    { {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.5f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } }, // 22
    { { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.5f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } }  // 23
};

unsigned int g_Indices[] = {
    0, 1, 2,
    2, 3, 0,

    6, 5, 4,
    4, 7, 6,

    8, 9, 10,
    10, 11, 8,

    12, 13, 14,
    14, 15, 12,

    16, 17, 18,
    18, 19, 16,
    
    20, 21, 22,
    22, 23, 20
};

GLFWwindow* g_WindowHandle = nullptr;

namespace Engine {
    void Renderer::Init(GLFWwindow* Handle, float Width, float Height) {

        g_WindowHandle = Handle;

        m_Camera = std::make_unique<Camera>(Width, Height, Vector3(0.0f, 0.0f, 2.0f));

        m_Context = RendererContext::Create();
        m_Context->Init(Handle);

        uint32_t vertexBufferSize = g_Vertices.size() * sizeof(Engine::Vertex);
        m_Vertex = VertexBuffer::Create(g_Vertices.data(), vertexBufferSize);
        m_Index = IndexBuffer::Create(g_Indices, sizeof(g_Indices));

        Assets::Shaders.Add("MainShader", Shader::Create("Engine/Assets/Base.shader"));
        Assets::Textures.Add("DebugTexture", Texture::Create("Engine/Assets/tex_DebugUVTiles.png"));
        Assets::Meshes.Add("Cube", Mesh::Create(std::move(m_Vertex), std::move(m_Index)));

        std::unique_ptr<Mesh3D> Cube;
        Cube = std::make_unique<Mesh3D>("MeshObj", "Cube", "DebugTexture", "MainShader");
        AddGameObject(std::move(Cube));

        std::unique_ptr<Mesh3D> Cube2;
        Cube2 = std::make_unique<Mesh3D>("MeshObj", "Cube", "DebugTexture", "MainShader");
        Cube2->transform.Position = Vector3(10.0f, 0.0f, 0.0f);
        AddGameObject(std::move(Cube2));
    }

    void Renderer::Draw() {

        m_Camera->Inputs(g_WindowHandle, Time::DeltaTime);

        m_Context->ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        m_Context->Clear();

        Assets::Shaders.Get("MainShader").SetMat4("projection", m_Camera->GetProjectionMatrix());
        Assets::Shaders.Get("MainShader").SetMat4("view", m_Camera->GetViewMatrix());

        for (auto& obj : GameObjects) {
            obj->Update(Time::DeltaTime);
            if (auto* meshOBJ = dynamic_cast<Mesh3D*>(obj.get())) { // Meshes
                meshOBJ->Render(m_Context.get());
            }
        }
    }

    void Renderer::Shutdown() {
        m_Context.reset();
        m_Vertex.reset();
        m_Index.reset();
        m_Camera.reset();
        ClearTree();
    }

}
