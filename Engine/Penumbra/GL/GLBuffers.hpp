#pragma once

#include "Penumbra/PBufferLayout.hpp"
#include "Penumbra/PBuffers.hpp"

namespace Engine {
    class GLVertexBuffer : public VertexBuffer {
        public:
            GLVertexBuffer(const void* Vertices, unsigned int Size);
            ~GLVertexBuffer() override;

            void Bind() override;
            void Unbind() override;

            unsigned int GetSize() override;
            void SetLayout(const BufferLayout& layout) override;
            const BufferLayout& GetLayout() const override;

        private:
            unsigned int m_VBO;
            unsigned int m_Size;
            BufferLayout m_Layout;
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