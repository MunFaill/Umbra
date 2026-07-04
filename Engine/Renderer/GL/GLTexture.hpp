#pragma once

#include "Renderer/RendererTexture.hpp"

namespace Engine {
	class GLTexture : public Texture {
		public:
			GLTexture(const std::string& TexturePath);
			~GLTexture() override;

			void Bind(unsigned int Slot = 0) override;
			void Unbind() override;
		private:
			unsigned int m_TBO; // Texture buffer object (I dont know if it's the correct name)
			std::string m_FilePath;
			unsigned char* m_LocalImageBuffer;
			int m_Width, m_Height, m_BPP;
	};
}
