#pragma once

#include "Renderer/RendererBuffers.hpp"
#include "Renderer/RendererContext.hpp"
#include "Renderer/RendererMesh.hpp"
#include "Renderer/RendererShader.hpp"
#include "Renderer/RendererTexture.hpp"

#include <glm/glm.hpp>
#include <memory>

class GLFWwindow;

namespace Engine {
    class Node3D;

    class Renderer {
        public:
            static void Init(GLFWwindow* Handle, float Width, float Height);
            static void Draw(Node3D* SceneRoot = nullptr);
            static void Shutdown();

        private:
            inline static std::unique_ptr<RendererContext> m_Context;
            inline static std::unique_ptr<VertexBuffer> m_Vertex;
            inline static std::unique_ptr<IndexBuffer> m_Index;
            inline static std::unique_ptr<Shader> m_Shader;
            inline static std::unique_ptr<Mesh> m_Mesh;
            inline static std::unique_ptr<Texture> m_Texture;
            inline static glm::mat4 m_View{1.0f};
            inline static glm::mat4 m_Projection{1.0f};
    };
}