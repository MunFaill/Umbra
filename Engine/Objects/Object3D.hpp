#pragma once

#include "Math/Transform.hpp"
#include "Objects/GameObject.hpp"

namespace Engine {
    class Object3D : public GameObject {
        public:
            Transform transform;

            inline Object3D(const std::string& name = "Object3D") : GameObject(name) {}
    };
}