#pragma once

#include <memory>
#include <string>

namespace Engine {
    class Texture {
        public:
            virtual ~Texture() = default;

            virtual void Bind(unsigned int Slot = 0) = 0;
            virtual void Unbind() = 0;

            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;

            static std::unique_ptr<Texture> Create(const std::string& Path);
            static std::unique_ptr<Texture> Create(unsigned int Width, unsigned int Height, unsigned char* Data);
    };
}
