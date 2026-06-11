#pragma once

#include <string>

class GLFWwindow;

namespace Engine {

    struct WindowProps {
        std::string WindowTitle;
        unsigned int Width, Height;
    };

    class Window {
        public:
            Window(WindowProps props = {"Umbra", 1360, 769});
            ~Window();

            void MakeContextCurrent();
            void HandleUpdate();
            bool ShouldClose();
            inline WindowProps GetProps() {return m_WindowProps;}
            inline GLFWwindow* GetHandle() {return m_WindowHandle;}
        private:
            WindowProps m_WindowProps;
            GLFWwindow* m_WindowHandle;
    };
}