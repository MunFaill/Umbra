#pragma once

#include "Platform/Window.hpp"
#include "Renderer/RendererContext.hpp"
#include "Objects/Node3D.hpp"

#include <memory>

namespace Engine {
    class Application {
        public:
            Application();
            virtual ~Application();

            void Run();

            virtual void OnInit();
            virtual void OnUpdate(float delta);

        protected:
            std::shared_ptr<Node3D> m_SceneRoot;

        private:
            std::unique_ptr<Window> m_Window;
    };
}