#include "Penumbra/GL/GLMesh.hpp"
#include "Penumbra/PBuffers.hpp"
#include "Tools/Log.hpp"

#include <glad/gl.h>
#include <utility>

namespace Engine {
    GLMesh::GLMesh(std::unique_ptr<VertexBuffer> Vertices, std::unique_ptr<IndexBuffer> Indices) : m_Vertices(std::move(Vertices)), m_Indices(std::move(Indices)){
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        m_Vertices->Bind();

        if (m_Indices) {
            m_Indices->Bind();
        }

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindVertexArray(0);

        m_Vertices->Unbind();
        if (m_Indices) {
            m_Indices->Unbind();
        }

        Print("Mesh created successfully");
    }

    GLMesh::~GLMesh() {
        glDeleteVertexArrays(1, &m_VAO);
        Print("Mesh deleted");
    }

    void GLMesh::Bind() {
        glBindVertexArray(m_VAO);
        Print("Mesh binded");
    }

    void GLMesh::Unbind() {
        glBindVertexArray(0);
        Print("Mesh unbinded");
    }

    unsigned int GLMesh::GetIndexCount() {
        if (m_Indices) {
            return m_Indices->GetCount();
        }
        return 0;
    }
}