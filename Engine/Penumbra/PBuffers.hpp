#pragma once

#include "Math/Common.hpp"
#include "Penumbra/PBufferLayout.hpp"

#include <memory>

namespace Engine {

    struct Vertex {
        Vector3 Position;
        Vector4 Colors;
        Vector2 UV;
        Vector3 Normals;

        static Engine::BufferLayout GetDefaultLayout() {
            return {
                { Engine::ShaderDataType::Float3, "a_Position" },
                { Engine::ShaderDataType::Float4, "a_Color"    },
                { Engine::ShaderDataType::Float2, "a_UV"       },
                { Engine::ShaderDataType::Float3, "a_Normal"   }
            };
        }
    };

    class VertexBuffer {
        public:
            virtual ~VertexBuffer() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual unsigned int GetSize() = 0;
            virtual void SetLayout(const BufferLayout& layout) = 0;

            virtual const BufferLayout& GetLayout() const = 0;

            static std::unique_ptr<VertexBuffer> Create(const void* Vertices, unsigned int Size);
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