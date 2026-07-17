#include "Penumbra/GL/GLMesh.hpp"
#include "Penumbra/PBufferLayout.hpp"
#include "Penumbra/PBuffers.hpp"
#include "Tools/Log.hpp"

#include <glad/gl.h>
#include <utility>

namespace Engine {

    static GLenum ShaderDataTypeToOpenGLBaseType(Engine::ShaderDataType type) {
        switch (type) {
            case Engine::ShaderDataType::Float:  return GL_FLOAT;
            case Engine::ShaderDataType::Float2: return GL_FLOAT;
            case Engine::ShaderDataType::Float3: return GL_FLOAT;
            case Engine::ShaderDataType::Float4: return GL_FLOAT;
            case Engine::ShaderDataType::Mat3:   return GL_FLOAT;
            case Engine::ShaderDataType::Mat4:   return GL_FLOAT;
            case Engine::ShaderDataType::Int:    return GL_INT;
            case Engine::ShaderDataType::Int2:   return GL_INT;
            case Engine::ShaderDataType::Int3:   return GL_INT;
            case Engine::ShaderDataType::Int4:   return GL_INT;
            case Engine::ShaderDataType::Bool:   return GL_BOOL;
        }
        return 0;
    }

    GLMesh::GLMesh(std::unique_ptr<VertexBuffer> Vertices, std::unique_ptr<IndexBuffer> Indices) : m_Vertices(std::move(Vertices)), m_Indices(std::move(Indices)){
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        m_Vertices->Bind();

        if (m_Indices) {
            m_Indices->Bind();
        }

        const BufferLayout& layout = m_Vertices->GetLayout();
        unsigned int index = 0;
        
        for (const BufferElement& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (void*)element.Offset);
            index++;
        }

        glBindVertexArray(0);

        m_Vertices->Unbind();
        if (m_Indices) {
            m_Indices->Unbind();
        }

        Print(Message, "Mesh created successfully");
    }

    GLMesh::~GLMesh() {
        glDeleteVertexArrays(1, &m_VAO);
        Print(Warning, "Mesh deleted");
    }

    void GLMesh::Bind() {
        glBindVertexArray(m_VAO);
    }

    void GLMesh::Unbind() {
        glBindVertexArray(0);
    }

    unsigned int GLMesh::GetIndexCount() {
        if (m_Indices) {
            return m_Indices->GetCount();
        }
        return 0;
    }
}