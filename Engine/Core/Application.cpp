#include "Core/Application.hpp"

namespace Engine {
    Application::Application() {
        OnInit();
    }

    Application::~Application() {

    }

    void Application::Run() {
        while (true) {
            OnUpdate(69.0f);
        }
    }
}