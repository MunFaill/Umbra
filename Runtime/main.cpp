#include "Objects/Mesh3D.hpp"
#include "Objects/ObjectTree.hpp"
#include <Umbra.hpp>
#include <memory>

std::unique_ptr<Engine::Mesh3D> Cube;

class Runtime : public Engine::Application {
    public:
        Runtime() = default;
        ~Runtime() override = default;

        void OnInit() override {
            // On scene init
        }

        void OnUpdate(float delta) override {
            // On scene update
            if (Engine::Mesh3D* cube = dynamic_cast<Engine::Mesh3D*>(Engine::FindGameObject("MeshObj")))
                cube->transform.Rotation.y += 90.0f * delta;
        }
};

int main() {
    Runtime* app = new Runtime();
    Cube = std::make_unique<Engine::Mesh3D>("MeshObj", "Cube", "DebugTexture", "MainShader");
    Engine::AddGameObject(std::move(Cube));
    app->Run();
    delete app;
}
