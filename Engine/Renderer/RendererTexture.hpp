#pragma once

#include <memory>
#include <string>

namespace Engine {
	class Texture {
		public:
			virtual ~Texture() = default;

			virtual void Bind(unsigned int Slot = 0) = 0;
			virtual void Unbind() = 0;

			static std::unique_ptr<Texture> Create(const std::string& TexturePath);
	};
}
