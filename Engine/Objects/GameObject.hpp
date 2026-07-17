#pragma once

#include "Tools/Log.hpp"

#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace Engine {
    class GameObject {
        protected:
            std::string Name;
            GameObject* Parent;
            std::vector<std::unique_ptr<GameObject>> Childrens;
        public:
            inline GameObject(const std::string& name = "Object") : Name(name) {}

            virtual ~GameObject() = default;

            inline virtual void Init() { Print(Message, "Object initialized: {}", this->GetName()); }
            inline virtual void Update(float DeltaTime) {
                for (auto& child : Childrens) {
                    child->Update(DeltaTime);
                }
            }

            inline void AddChild(std::unique_ptr<GameObject> child) {
                child->Parent = this;
                child->Init();
                Childrens.push_back(std::move(child));
            }

            inline void SetParent(GameObject* parent) {Parent = parent;}

            GameObject* GetParent() const {return Parent;}
            const std::string& GetName() const {return Name;}
    };
}