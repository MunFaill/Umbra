#include "Core/Application.hpp"
#include "Platform/WindowBackend.hpp"
#include "Math/Time.hpp"
#include "Tools/Event.hpp"

#include <print>

namespace Engine {
    Application::Application() {
        WindowBackend::Init();
        m_Window = std::make_unique<Window>();
        OnInit();
        Events::OnInit.Invoke();
        std::print("Application initialized\n");
    }

    Application::~Application() {
        std::print("Application shutdown\n");
        m_Window.reset();
        WindowBackend::Shutdown();
        Events::OnInit.RemoveAllListeners();
        Events::OnUpdate.RemoveAllListeners();
    }

    void Application::Run() {
        m_Window->MakeContextCurrent();
        Time::InitTime();
        std::print("Application running\n");
        while (!m_Window->ShouldClose()) {
            Time::CalculateTime();
            Events::OnUpdate.Invoke(Time::DeltaTime);
            OnUpdate(Time::DeltaTime);
            m_Window->HandleUpdate();
        }
    }

    void Application::OnInit() {}
    void Application::OnUpdate(float dt) {}
}