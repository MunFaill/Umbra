#pragma once

#include "Penumbra/PBuffers.hpp"
#include "Penumbra/PContext.hpp"

#include <glm/glm.hpp>
#include <memory>

class GLFWwindow;

namespace Engine {

    class Renderer {
        public:
            static void Init(GLFWwindow* Handle);
            static void Draw(unsigned int Widht, unsigned int Height);
            static void Shutdown();

        private:
            inline static std::unique_ptr<RendererContext> m_Context;
            inline static std::unique_ptr<VertexBuffer> m_Vertex;
            inline static std::unique_ptr<IndexBuffer> m_Index;
    };
}