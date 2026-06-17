#pragma once

#include "Platform/Window.hpp"
#include "Renderer/RendererContext.hpp"

#include <memory>

namespace Engine {
    class Application {
        public:
            Application();
            ~Application();

            void Run();

            virtual void OnInit();
            virtual void OnUpdate(float delta);
        private:
            std::unique_ptr<Window> m_Window;
    };
}