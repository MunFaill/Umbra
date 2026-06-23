#pragma once

#include "Renderer/RendererTexture.hpp"

namespace Engine {
    class GLTexture : public Texture {
        public:
            GLTexture(const std::string& Path);
            GLTexture(unsigned int Width, unsigned int Height, unsigned char* Data);
            ~GLTexture() override;

            void Bind(unsigned int Slot = 0) override;
            void Unbind() override;

            unsigned int GetWidth() const override { return m_Width; }
            unsigned int GetHeight() const override { return m_Height; }

        private:
            void Init(unsigned int Width, unsigned int Height, unsigned char* Data);

            unsigned int m_TextureID = 0;
            unsigned int m_Width = 0;
            unsigned int m_Height = 0;
    };
}
