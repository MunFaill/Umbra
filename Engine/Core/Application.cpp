#include "Core/Application.hpp"
#include "Platform/WindowBackend.hpp"
#include "Math/Time.hpp"
#include "Tools/Log.hpp"
#include "Penumbra/PRenderer.hpp"

namespace Engine {
    Application::Application() {
        WindowBackend::Init();
        m_Window = std::make_unique<Window>();
        WindowProps props = m_Window->GetProps();
        Renderer::Init(m_Window->GetHandle(), static_cast<float>(props.Width), static_cast<float>(props.Height));
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
            Renderer::Draw();
            m_Window->HandleUpdate();
        }
    }

    void Application::OnInit() {}
    void Application::OnUpdate(float dt) {}
}