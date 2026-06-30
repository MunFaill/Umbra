#pragma once

#include "Renderer/RendererBuffers.hpp"

namespace Engine {
    class GLVertexBuffer : public VertexBuffer {
        public:
            GLVertexBuffer(float Vertices[], unsigned int Size);
            ~GLVertexBuffer() override;

            void Bind() override;
            void Unbind() override;

            unsigned int GetSize() override;

        private:
            unsigned int m_VBO;
            unsigned int m_Size;
    };

    class GLIndexBuffer : public IndexBuffer {
        public:
            GLIndexBuffer(unsigned int Indices[], unsigned int Count);
            ~GLIndexBuffer() override;

            void Bind() override;
            void Unbind() override;

            unsigned int GetCount() override;

        private:
            unsigned int m_EBO;
            unsigned int m_Count;
    };

    class GLFrameBuffer : public FrameBuffer {
        public:
            GLFrameBuffer();
            ~GLFrameBuffer() override;

            void Bind() override;
            void Unbind() override;

        private:
            unsigned int m_FBO;
    };
}