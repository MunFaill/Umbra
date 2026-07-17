#pragma once

#include "Tools/Log.hpp"

#include "Objects/GameObject.hpp"
#include "Objects/Object3D.hpp"
#include "Objects/Mesh3D.hpp"
#include "Objects/Camera3D.hpp"

#include <utility>
#include <vector>
#include <memory>

namespace Engine {
    inline std::vector<std::unique_ptr<GameObject>> GameObjects;

    inline void AddGameObject(std::unique_ptr<GameObject> obj) {
        obj->Init();
        Print(Message, "Object added to tree: {}", obj->GetName());
        GameObjects.push_back(std::move(obj));
    }

    inline void RemoveGameObject(std::unique_ptr<GameObject> obj) {
        Print(Message, "Object removed from tree: {}", obj->GetName());
        std::erase(GameObjects, obj);
    }

    inline GameObject* FindGameObject(const std::string& name) {
        for (auto& obj : GameObjects) {
            if (obj && obj->GetName() == name) {
                return obj.get();
            }
        }
        return nullptr;
    }

    inline void ClearTree() {
        GameObjects.clear();
        Print(Warning, "Tree clear");
    }
}