#pragma once

#include <memory>

class GLFWwindow;

namespace Engine {

    enum class GraphicsAPI {
        None = 0, OpenGL = 1, Vulkan = 2
    };

    class RendererContext {
        public:
            virtual ~RendererContext() = default;

            virtual void Init(GLFWwindow* Handle) = 0;
            virtual void ClearColor(float r, float g, float b, float a) = 0;
            virtual void DrawIndexed(unsigned int Size) = 0;
            virtual void Clear() = 0;

            static GraphicsAPI GetGraphicsAPI();
            static std::unique_ptr<RendererContext> Create();
    };
}