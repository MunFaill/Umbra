#include "Penumbra/GL/GLBuffers.hpp"
#include "Tools/Log.hpp"

#include <glad/gl.h>

namespace Engine {

    // Vertex Buffer

    GLVertexBuffer::GLVertexBuffer(float Vertices[], unsigned int Size) : m_Size(Size) {
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        Print("Vertex Buffer created: {}", m_VBO);
    };

    GLVertexBuffer::~GLVertexBuffer() {
        glDeleteBuffers(1, &m_VBO);
        Print("Vertex Buffer deleted: {}", m_VBO);
    }

    void GLVertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        Print("Vertex Buffer binded: {}", m_VBO);
    }

    void GLVertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        Print("Vertex Buffer unbinded: {}", m_VBO);
    }

    unsigned int GLVertexBuffer::GetSize() {
        return m_Size;
    }

    // Index Buffer

    GLIndexBuffer::GLIndexBuffer(unsigned int Indices[], unsigned int Count) : m_Count(Count) {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count, Indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        Print("Index Buffer Created: {}", m_EBO);
    }

    GLIndexBuffer::~GLIndexBuffer() {
        glDeleteBuffers(1, &m_EBO);
        Print("Index Buffer deleted: {}", m_EBO);
    }

    void GLIndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        Print("Index Buffer binded: {}", m_EBO);
    }

    void GLIndexBuffer::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        Print("Index Buffer unbinded: {}", m_EBO);
    }

    unsigned int GLIndexBuffer::GetCount() {
        return  m_Count;
    }

    // Frame Buffer

    GLFrameBuffer::GLFrameBuffer() {
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
            Print("Frame buffer complete\n");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        Print("Frame Buffer created: {}\n", m_FBO);
    }

    GLFrameBuffer::~GLFrameBuffer() {
        glDeleteFramebuffers(1, &m_FBO);
        Print("Frame Buffer deleted: {}\n", m_FBO);
    }

    void GLFrameBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        Print("Frame Buffer binded: {}\n", m_FBO);
    }

    void GLFrameBuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        Print("Frame Buffer unbinded: {}\n", m_FBO);
    }
}