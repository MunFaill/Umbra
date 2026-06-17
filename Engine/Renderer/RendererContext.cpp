#include "Renderer/RendererContext.hpp"
#include "Renderer/RendererBuffers.hpp"
#include "Renderer/RendererShader.hpp"
#include "Renderer/RendererMesh.hpp"

#include "Renderer/GL/GLContext.hpp"
#include "Renderer/GL/GLBuffers.hpp"
#include "Renderer/GL/GLShader.hpp"
#include "Renderer/GL/GLMesh.hpp"

#include <memory>

namespace Engine {
    GraphicsAPI g_GraphicsAPI = GraphicsAPI::OpenGL;

    GraphicsAPI RendererContext::GetGraphicsAPI() {
        return g_GraphicsAPI;
    }

    // Renderer Context
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

    // Vertex Buffer
    std::unique_ptr<VertexBuffer> VertexBuffer::Create(float Vertices[], unsigned int Size) {
        switch (g_GraphicsAPI) {
            case GraphicsAPI::None:
                return nullptr;
            case GraphicsAPI::OpenGL:
                return std::make_unique<GLVertexBuffer>(Vertices, Size);
            case GraphicsAPI::Vulkan:
                return nullptr;
        }
        return nullptr;
    }

    // Index Buffer
    std::unique_ptr<IndexBuffer> IndexBuffer::Create(unsigned int Indices[], unsigned int Count) {
        switch (g_GraphicsAPI) {
            case GraphicsAPI::None:
                return nullptr;
            case GraphicsAPI::OpenGL:
                return std::make_unique<GLIndexBuffer>(Indices, Count);
            case GraphicsAPI::Vulkan:
                return nullptr;
        }
        return nullptr;
    }

    // Frame Buffer
    std::unique_ptr<FrameBuffer> FrameBuffer::Create() {
        switch (g_GraphicsAPI) {
            case GraphicsAPI::None:
                return nullptr;
            case GraphicsAPI::OpenGL:
                return std::make_unique<GLFrameBuffer>();
            case GraphicsAPI::Vulkan:
                return nullptr;
        }
        return nullptr;
    }

    std::unique_ptr<Shader> Shader::Create(std::string VertexShaderPath, std::string FragmentShaderPath) {
        switch (g_GraphicsAPI) {
            case GraphicsAPI::None:
                return nullptr;
            case GraphicsAPI::OpenGL:
                return std::make_unique<GLShader>(VertexShaderPath, FragmentShaderPath);
            case GraphicsAPI::Vulkan:
                return nullptr;
        }
        return nullptr;
    }

    std::unique_ptr<Mesh> Mesh::Create(std::unique_ptr<VertexBuffer> Vertices, std::unique_ptr<IndexBuffer> Indices) {
        switch (g_GraphicsAPI) {
            case GraphicsAPI::None:
                return nullptr;
            case GraphicsAPI::OpenGL:
                return std::make_unique<GLMesh>(std::move(Vertices), std::move(Indices));
            case GraphicsAPI::Vulkan:
                return nullptr;
        }
        return nullptr;
    }
}