#include "Renderer/GL/GLTexture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/gl.h>
#include <print>

namespace Engine {
    void GLTexture::Init(unsigned int Width, unsigned int Height, unsigned char* Data) {
        m_Width = Width;
        m_Height = Height;

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLTexture::GLTexture(const std::string& Path) {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        unsigned char* data = stbi_load(Path.c_str(), &width, &height, &channels, 4);

        if (!data) {
            std::println("Error: Failed to load texture: {}", Path);
            return;
        }

        Init(static_cast<unsigned int>(width), static_cast<unsigned int>(height), data);
        stbi_image_free(data);

        std::println("Texture loaded from file: {} ({}x{})", Path, m_Width, m_Height);
    }

    GLTexture::GLTexture(unsigned int Width, unsigned int Height, unsigned char* Data) {
        Init(Width, Height, Data);
        std::println("Texture created: {} ({}x{})", m_TextureID, m_Width, m_Height);
    }

    GLTexture::~GLTexture() {
        if (m_TextureID != 0) {
            glDeleteTextures(1, &m_TextureID);
            std::println("Texture deleted: {}", m_TextureID);
        }
    }

    void GLTexture::Bind(unsigned int Slot) {
        glActiveTexture(GL_TEXTURE0 + Slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        std::println("Texture binded: {} (slot {})", m_TextureID, Slot);
    }

    void GLTexture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
        std::println("Texture unbinded: {}", m_TextureID);
    }
}
