#include "Renderer/GL/GLBuffers.hpp"

#include <glad/gl.h>
#include <print>

namespace Engine {

    /*
        Vertex Buffer
    */

    GLVertexBuffer::GLVertexBuffer(float Vertices[], unsigned int Size) {
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        std::println("Vertex Buffer created: {}", m_VBO);
    };

    GLVertexBuffer::~GLVertexBuffer() {
        glDeleteBuffers(1, &m_VBO);
        std::println("Vertex Buffer deleted: {}", m_VBO);
    }

    void GLVertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        std::println("Vertex Buffer binded: {}", m_VBO);
    }

    void GLVertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        std::println("Vertex Buffer unbinded: {}", m_VBO);
    }

    /*
        Index Buffer
    */

    GLIndexBuffer::GLIndexBuffer(unsigned int Indices[], unsigned int Count) {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count, Indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        std::println("Index Buffer Created: {}", m_EBO);
    }

    GLIndexBuffer::~GLIndexBuffer() {
        glDeleteBuffers(1, &m_EBO);
        std::println("Index Buffer deleted: {}", m_EBO);
    }

    void GLIndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        std::println("Index Buffer binded: {}", m_EBO);
    }

    void GLIndexBuffer::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        std::println("Index Buffer unbinded: {}", m_EBO);
    }

    /*
        FRAME BUFFER
    */

    GLFrameBuffer::GLFrameBuffer() {
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
            std::println("Frame buffer complete\n");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        std::println("Frame Buffer created: {}\n", m_FBO);
    }

    GLFrameBuffer::~GLFrameBuffer() {
        glDeleteFramebuffers(1, &m_FBO);
        std::println("Frame Buffer deleted: {}\n", m_FBO);
    }

    void GLFrameBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        std::println("Frame Buffer binded: {}\n", m_FBO);
    }

    void GLFrameBuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        std::println("Frame Buffer unbinded: {}\n", m_FBO);
    }
}