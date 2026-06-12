#include "Renderer/GL/GLBuffers.hpp"

#define GLAD_GL_IMPLEMENTATION
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
        std::print("Vertex Buffer created: {}\n", m_VBO);
    };

    GLVertexBuffer::~GLVertexBuffer() {
        glDeleteBuffers(1, &m_VBO);
        std::print("Vertex Buffer deleted: {}\n", m_VBO);
    }

    void GLVertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        std::print("Vertex Buffer binded: {}\n", m_VBO);
    }

    void GLVertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        std::print("Vertex Buffer unbinded: {}\n", m_VBO);
    }

    /*
        Index Buffer
    */

    GLIndexBuffer::GLIndexBuffer(unsigned int Indices[], unsigned int Count) {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count, Indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        std::print("Index Buffer Created: {}\n", m_EBO);
    }

    GLIndexBuffer::~GLIndexBuffer() {
        glDeleteBuffers(1, &m_EBO);
        std::print("Index Buffer deleted: {}\n", m_EBO);
    }

    void GLIndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        std::print("Index Buffer binded: {}\n", m_EBO);
    }

    void GLIndexBuffer::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        std::print("Index Buffer unbinded: {}\n", m_EBO);
    }

    /*
        FRAME BUFFER
    */

    GLFrameBuffer::GLFrameBuffer() {
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
            std::print("Frame buffer complete\n");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        std::print("Frame Buffer created: {}\n", m_FBO);
    }

    GLFrameBuffer::~GLFrameBuffer() {
        glDeleteFramebuffers(1, &m_FBO);
        std::print("Frame Buffer deleted: {}\n", m_FBO);
    }

    void GLFrameBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        std::print("Frame Buffer binded: {}\n", m_FBO);
    }

    void GLFrameBuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        std::print("Frame Buffer unbinded: {}\n", m_FBO);
    }
}