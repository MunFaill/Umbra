#pragma once

#include <Umbra.hpp>

class FlyCamera : public Engine::Camera3D {
    public:
        inline FlyCamera(const std::string& name, float fovy, bool current) 
            : Camera3D(name, fovy, current) 
        {
            transform.Rotation = Vector3(0.0f, -90.0f, 0.0f);
        }

        float Speed = 10.5f;
        float Sensitivity = 100.0f;

        float Yaw = -90.0f;
        float Pitch = 0.0f;
        bool FirstClick = true;

        Vector3 Orientation = Vector3(0.0f, 0.0f, -1.0f);

        inline void Init() override {}

        inline void Update(float delta) override {
            if (Engine::IsMouseButtonPressed(Engine::MOUSE_RIGHT)) {
                Engine::ShowCursor(true);

                double MX, MY;
                Engine::GetCursorPos(MX, MY);

                float width = (float)Engine::CurrentWindowProp->Width;
                float height = (float)Engine::CurrentWindowProp->Height;

                if (FirstClick) {
                    MX = width / 2.0;
                    MY = height / 2.0;
                    Engine::SetCursorPos(MX, MY);
                    FirstClick = false;
                }

                float rotX = (float)(MX - (width / 2.0f)) / width;
                float rotY = (float)(MY - (height / 2.0f)) / height;

                Yaw   += rotX * Sensitivity;
                Pitch -= rotY * Sensitivity;

                if (Pitch > 89.0f) Pitch = 89.0f;
                if (Pitch < -89.0f) Pitch = -89.0f;

                transform.Rotation = Vector3(Pitch, Yaw, 0.0f);

                Engine::SetCursorPos(width / 2.0f, height / 2.0f);
            } else {
                Engine::ShowCursor(false);
                FirstClick = true;
            }

            float radYaw   = DegToRadians(transform.Rotation.y);
            float radPitch = DegToRadians(transform.Rotation.x);

            Vector3 direction;
            direction.x = cos(radYaw) * cos(radPitch);
            direction.y = sin(radPitch);
            direction.z = sin(radYaw) * cos(radPitch);
            Orientation = Normalize(direction);

            float velocity = Speed * delta;

            if (Engine::IsKeyPressed(Engine::KEY_W))
                transform.Position += velocity * Orientation;
            if (Engine::IsKeyPressed(Engine::KEY_S))
                transform.Position -= velocity * Orientation;

            Vector3 rightDirection = Normalize(Cross(Orientation, Vector3UP));
            if (Engine::IsKeyPressed(Engine::KEY_A))
                transform.Position -= velocity * rightDirection;
            if (Engine::IsKeyPressed(Engine::KEY_D))
                transform.Position += velocity * rightDirection;

            if (Engine::IsKeyPressed(Engine::KEY_SPACE))
                transform.Position += velocity * Vector3UP;
            if (Engine::IsKeyPressed(Engine::KEY_LEFT_SHIFT))
                transform.Position += velocity * Vector3Down;
        }
};