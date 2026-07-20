#include "Math/Common.hpp"
#include <Umbra.hpp>
#include <memory>
#include <utility>

class Runtime : public Engine::Application {
    public:
        Runtime() = default;
        ~Runtime() override = default;

        void OnInit() override {
            // On scene init

            // Create and add a shader to assets
            Engine::Assets::Shaders.Add("MainShader", Engine::Shader::Create("Engine/Assets/Base.shader"));

            // Texture
            Engine::Assets::Textures.Add("DefaultTexture", Engine::Texture::Create("Engine/Assets/default.png"));

            // Material with basic data
            Engine::Assets::Materials.Add("MyMaterial", std::make_unique<Engine::Material>());

            // Model
            std::unique_ptr<Engine::Model> model = std::make_unique<Engine::Model>();
            model->LoadMeshFromFile("Engine/Assets/lampshade.obj");
            model->SetMaterial("MyMaterial");
            Engine::Assets::Models.Add("Model", std::move(model));

            // Game Objects: Camera3D
            std::unique_ptr<Engine::Camera3D> cam;
            cam = std::make_unique<Engine::Camera3D>("MyCamera", 75.0f, true);
            cam->transform.Position = Vector3(0.0f, 0.5f, 10.0f);
            Engine::AddGameObject(std::move(cam));

            // Model3D
            std::unique_ptr<Engine::Model3D> MyModel;
            MyModel = std::make_unique<Engine::Model3D>("MyModel", "Model", "MainShader");
            Engine::AddGameObject(std::move(MyModel));
        }

        void OnUpdate(float delta) override {
            // On scene update
            if (Engine::Model3D* model = dynamic_cast<Engine::Model3D*>(Engine::FindGameObject("MyModel"))) {
                model->transform.Rotation.z += -90.0f * delta;
            }
        }
};

int main() {
    Runtime* app = new Runtime();
    app->Run();
    delete app;
}
