#include "Core/Application.hpp"
#include "Platform/WindowBackend.hpp"
#include "Math/Time.hpp"
#include "Tools/Log.hpp"
#include "Penumbra/PRenderer.hpp"

namespace Engine {
    Application::Application() {
        WindowBackend::Init();
        m_Window = std::make_unique<Window>();
        Renderer::Init(m_Window->GetHandle());
        OnInit();
        Print("Application initialized");
    }

    Application::~Application() {
        Print("Application shutdown");
        Renderer::Shutdown();
        m_Window.reset();
        WindowBackend::Shutdown();
    }

    void Application::Run() {
        Time::InitTime();
        Print("Application running");
        while (!m_Window->ShouldClose()) {
            Time::CalculateTime();
            OnUpdate(Time::DeltaTime);
            Renderer::Draw(static_cast<float>(m_Window->GetProps().Width), static_cast<float>(m_Window->GetProps().Height));
            m_Window->HandleUpdate();
        }
    }

    void Application::OnInit() {}
    void Application::OnUpdate(float dt) {}
}