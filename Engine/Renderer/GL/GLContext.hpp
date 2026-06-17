#pragma once

#include "Renderer/RendererContext.hpp"

namespace Engine {

    class GLContext : public RendererContext {
        public:
            GLContext();
            ~GLContext() override;
            void Init(GLFWwindow* Handle) override;
            void ClearColor(float r, float g, float b, float a) override;
            void DrawInstancied(unsigned int Size) override;
            void Clear() override;
    };
}