#include "Renderer/RendererContext.hpp"
#include "Renderer/GL/GLContext.hpp"
#include <memory>

namespace Engine {
    GraphicsAPI g_GraphicsAPI = GraphicsAPI::OpenGL;

    GraphicsAPI RendererContext::GetGraphicsAPI() {
        return g_GraphicsAPI;
    }

    std::unique_ptr<RendererContext> RendererContext::Create() {
        switch (g_GraphicsAPI) {
            case GraphicsAPI::None:
                return nullptr;
            case GraphicsAPI::OpenGL:
                return std::make_unique<GLContext>();
            case GraphicsAPI::Vulkan:
                return nullptr;
        }
        return nullptr;
    }
}