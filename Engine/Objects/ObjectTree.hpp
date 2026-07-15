#pragma once

#include "Objects/GameObject.hpp"
#include "Objects/Object3D.hpp"
#include "Objects/Mesh3D.hpp"

#include <utility>
#include <vector>
#include <memory>

namespace Engine {
    inline std::vector<std::unique_ptr<GameObject>> GameObjects;

    inline void AddGameObject(std::unique_ptr<GameObject> obj) {
        GameObjects.push_back(std::move(obj));
    }

    inline void RemoveGameObject(std::unique_ptr<GameObject> obj) {
        std::erase(GameObjects, obj);
    }

    inline void ClearTree() {
        GameObjects.clear();
    }
}