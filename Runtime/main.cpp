#include <Umbra.hpp>

class Runtime : public Engine::Application {
    public:
        Runtime() = default;
        ~Runtime() override = default;

        void OnInit() override {
            m_SceneRoot = std::make_shared<Engine::Node3D>("Root");
        }

        void OnUpdate(float delta) override {
            if (m_SceneRoot) {
                m_SceneRoot->Rotation.y += delta;
            }
        }
};

int main() {
    Runtime* app = new Runtime();
    app->Run();
    delete app;
}
