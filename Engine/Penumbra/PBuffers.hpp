#pragma once

#include <memory>

namespace Engine {
    class VertexBuffer {
        public:
            virtual ~VertexBuffer() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual unsigned int GetSize() = 0;

            static std::unique_ptr<VertexBuffer> Create(float Vertices[], unsigned int Size);
    };  

    class IndexBuffer {
        public:
            virtual ~IndexBuffer() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual unsigned int GetCount() = 0;

            static std::unique_ptr<IndexBuffer> Create(unsigned int Indices[], unsigned int Count);
    };

    class FrameBuffer {
        public:
            virtual ~FrameBuffer() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            static std::unique_ptr<FrameBuffer> Create();
    };
}