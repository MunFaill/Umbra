#include "Core/Application.hpp"

#include "Platform/Windowing/WindowBackend.hpp"
#include "Platform/Windowing/Window.hpp"

#include "Objects/ObjectTree.hpp"

#include "Tools/Log.hpp"

#include "Math/Time.hpp"

#include "Penumbra/PRenderer.hpp"

#include "Platform/IO/Input.hpp"

namespace Engine {
    Application::Application() {
        // Init everthing
        Print(Message, "Application initialized");

        Time::InitTime();
        WindowBackend::Initialize();
        m_Window = std::make_unique<Window>();
        Renderer::Init(m_Window->GetHandle());

        CurrentInputContext = m_Window->GetHandle();
    }

    Application::~Application() {
        Print(Warning, "Application shutdown and delete");
        // Shutdown everthing
        WindowBackend::Shutdown();
        m_Window.reset();
        Renderer::Shutdown();
    }

    void Application::Run() {
        Print(Message, "Application running");
        OnInit();
        while (m_IsRunning) {

            Time::CalculateTime();

            if (m_Window->ShouldClose()) {
                m_IsRunning = false;
            }

            m_Window->HandleUpdate();

            Renderer::Draw(m_Window->GetProps().Width, m_Window->GetProps().Height);

            for (auto& obj : GameObjects) {
                obj->Update(Time::DeltaTime);
            }

            OnUpdate(Time::DeltaTime); // Needs to be the last one called
        }
    }
}