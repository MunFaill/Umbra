#pragma once

#include "Renderer/RendererMesh.hpp"

namespace Engine {
    class GLMesh : public Mesh {
        public:
            GLMesh(std::unique_ptr<VertexBuffer> Vertices, std::unique_ptr<IndexBuffer> Indices);
            ~GLMesh() override;

            void Bind() override;
            void Unbind() override;

            unsigned int GetIndexCount() override;

        private:
            std::unique_ptr<VertexBuffer> m_Vertices;
            std::unique_ptr<IndexBuffer> m_Indices;
            unsigned int m_VAO;
    };
}