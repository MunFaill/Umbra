#pragma once

#include "Renderer/RendererBuffers.hpp"
#include "Renderer/RendererContext.hpp"

#include <glm/glm.hpp>
#include <memory>

class GLFWwindow;

namespace Engine {

    class Renderer {
        public:
            static void Init(GLFWwindow* Handle, float Width, float Height);
            static void Draw();
            static void Shutdown();

        private:
            inline static std::unique_ptr<RendererContext> m_Context;
            inline static std::unique_ptr<VertexBuffer> m_Vertex;
            inline static std::unique_ptr<IndexBuffer> m_Index;
    };
}