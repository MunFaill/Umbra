#include <Umbra.hpp>
#include <memory>
#include <utility>

class Runtime : public Engine::Application {
    public:
        Runtime() = default;
        ~Runtime() override = default;

        void OnInit() override {
            // On scene init
        }

        void OnUpdate(float delta) override {
            // On scene update
            if (Engine::Camera3D* camera = dynamic_cast<Engine::Camera3D*>(Engine::FindGameObject("MyCamera")))
                camera->transform.Rotation.y += 90.0f * delta;

            if (Engine::Mesh3D* cube = dynamic_cast<Engine::Mesh3D*>(Engine::FindGameObject("MeshObj")))
                cube->transform.Rotation.y += 90.0f * delta;
        }
};

int main() {
    Runtime* app = new Runtime();

    std::unique_ptr<Engine::Camera3D> cam;
    cam = std::make_unique<Engine::Camera3D>("MyCamera", 75.0f, true);
    cam->transform.Position = Vector3(0.0f, 0.0f, 2.0f);
    Engine::AddGameObject(std::move(cam));

    std::unique_ptr<Engine::Mesh3D> cube;
    cube = std::make_unique<Engine::Mesh3D>("MeshObj", "Cube", "DebugTexture", "MainShader");
    Engine::AddGameObject(std::move(cube));

    app->Run();
    delete app;
}
