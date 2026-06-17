#pragma once

#include <memory>

namespace Engine {

    // Forward declaration
    class VertexBuffer;
    class IndexBuffer;

    class Mesh {
        public:
            virtual ~Mesh() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            static std::unique_ptr<Mesh> Create(std::unique_ptr<VertexBuffer> vertices, std::unique_ptr<IndexBuffer> indices);
    };
}