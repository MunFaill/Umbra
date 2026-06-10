#pragma once

namespace Engine {
    class Application {
        public:
            Application();
            ~Application();

            void Run();

            virtual void OnInit();
            virtual void OnUpdate(float delta);
    };
}