#include "Penumbra/GL/GLTexture.hpp"
#include "Tools/Log.hpp"
#include <cstddef>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/gl.h>

namespace Engine {
	GLTexture::GLTexture(const std::string& TexturePath) {
		stbi_set_flip_vertically_on_load(1);
		m_LocalImageBuffer = stbi_load(TexturePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_TBO);
		glBindTexture(GL_TEXTURE_2D, m_TBO);
  glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalImageBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_LocalImageBuffer) {
			stbi_image_free(m_LocalImageBuffer);
		}

		Print(Message, "Texture created with success");
	}

	GLTexture::~GLTexture() {
		Print(Warning, "Texture deleted: {}", m_TBO);
		glDeleteTextures(1, &m_TBO);
	}

	void GLTexture::Bind(unsigned int Slot) {
		glActiveTexture(GL_TEXTURE0 + Slot);
		glBindTexture(GL_TEXTURE_2D, m_TBO);
	}

	void GLTexture::Unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
