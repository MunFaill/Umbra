#include <Umbra.hpp>

class Runtime : public Engine::Application {
    public:
        Runtime() {

        }

        ~Runtime() {

        }

        void OnInit() override {

        }

        void OnUpdate(float delta) override {

        }
};

int main() {
    Runtime* app = new Runtime();
    app->Run();
    delete app;
}