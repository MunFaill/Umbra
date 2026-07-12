#include "Penumbra/PContext.hpp"
#include "Penumbra/PBuffers.hpp"
#include "Penumbra/PShader.hpp"
#include "Penumbra/PMesh.hpp"
#include "Penumbra/PTexture.hpp"

#include "Penumbra/GL/GLContext.hpp"
#include "Penumbra/GL/GLBuffers.hpp"
#include "Penumbra/GL/GLShader.hpp"
#include "Penumbra/GL/GLMesh.hpp"
#include "Penumbra/GL/GLTexture.hpp"

#include <memory>

namespace Engine {
    GraphicsAPI g_GraphicsAPI = GraphicsAPI::OpenGL;

    GraphicsAPI RendererContext::GetGraphicsAPI() {
        return g_GraphicsAPI;
    }

    bool RendererContext::IsAPINone() {
        if (g_GraphicsAPI == GraphicsAPI::None) {
            return true;
        }

        return false;
    }

    bool RendererContext::IsAPIGL() {
        if (g_GraphicsAPI == GraphicsAPI::OpenGL) {
            return true;
        }

        return false;
    }

    bool RendererContext::IsAPIVK() {
        if (g_GraphicsAPI == GraphicsAPI::Vulkan) {
            return true;
        }

        return false;
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
    std::unique_ptr<VertexBuffer> VertexBuffer::Create(const void* Vertices, unsigned int Size) {
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

    // Shader
    std::unique_ptr<Shader> Shader::Create(const std::string& ShaderPath) {
        switch (g_GraphicsAPI) {
            case GraphicsAPI::None:
                return nullptr;
            case GraphicsAPI::OpenGL:
                return std::make_unique<GLShader>(ShaderPath);
            case GraphicsAPI::Vulkan:
                return nullptr;
        }
        return nullptr;
    }

    // Mesh
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

    // Texture
    std::unique_ptr<Texture> Texture::Create(const std::string& FilePath) {
    	switch (g_GraphicsAPI) {
    		case GraphicsAPI::None:
    			return nullptr;
    		case GraphicsAPI::OpenGL:
    			return std::make_unique<GLTexture>(FilePath);
    		case GraphicsAPI::Vulkan:
    			return nullptr;
    	}
    	return nullptr;
    }
}
