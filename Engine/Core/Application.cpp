#include "Core/Application.hpp"
#include "Platform/WindowBackend.hpp"
#include "Math/Time.hpp"
#include "Tools/Event.hpp"

#include "Renderer/Renderer.hpp"

#include <print>

namespace Engine {
    Application::Application() {
        WindowBackend::Init();
        m_Window = std::make_unique<Window>();
        Renderer::Init(m_Window->GetHandle());
        OnInit();
        Events::OnInit.Invoke();
        std::println("Application initialized");
    }

    Application::~Application() {
        std::println("Application shutdown");
        Renderer::Shutdown();
        m_Window.reset();
        WindowBackend::Shutdown();
        Events::OnInit.RemoveAllListeners();
        Events::OnUpdate.RemoveAllListeners();
    }

    void Application::Run() {
        Time::InitTime();
        std::println("Application running");
        while (!m_Window->ShouldClose()) {
            Time::CalculateTime();
            Events::OnUpdate.Invoke(Time::DeltaTime);
            OnUpdate(Time::DeltaTime);
            Renderer::Draw();
            m_Window->HandleUpdate();
        }
    }

    void Application::OnInit() {}
    void Application::OnUpdate(float dt) {}
}