#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>
#include <vector>

namespace Engine {

    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static unsigned int ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;
        }
        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        unsigned int Size;
        size_t Offset;
        bool Normalized;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}
        unsigned int GetComponentCount() const {
            switch (Type) {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3;
                case ShaderDataType::Mat4:   return 4; 
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
            }
            return 0;
        }
    };

    class BufferLayout {
        public:
            BufferLayout() = default;
            BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
                CalculateOffsetAndStride();
            }

            unsigned int GetStride() const {return m_Stride;}
            const std::vector<BufferElement>& GetElement() const {return m_Elements;}

            std::vector<BufferElement>::iterator begin() {return m_Elements.begin();}
            std::vector<BufferElement>::iterator end() {return m_Elements.end();}
            std::vector<BufferElement>::const_iterator begin() const {return m_Elements.begin();}
            std::vector<BufferElement>::const_iterator end() const {return m_Elements.end();}

        private:
            void CalculateOffsetAndStride() {
                size_t offset = 0;
                m_Stride = 0;
                for (BufferElement& element : m_Elements) {
                    element.Offset = offset;
                    offset += element.Size;
                    m_Stride += element.Size;
                }
            }

            std::vector<BufferElement> m_Elements;
            unsigned int m_Stride = 0;
    };
}