#pragma once

#include <memory>

namespace Engine {

    // Forward declaration
    class Window;

    class Application {
        public:
            Application();
            virtual ~Application();

            inline virtual void OnInit() {}
            inline virtual void OnUpdate(float DTime) {}
            
            void Run();
        private:
            bool m_IsRunning = true;
            std::unique_ptr<Window> m_Window;
    };
}