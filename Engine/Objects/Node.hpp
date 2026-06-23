#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Engine {
    class Node : public std::enable_shared_from_this<Node> {
        protected:
            std::string Name;
            std::weak_ptr<Node> Parent;
            std::vector<std::shared_ptr<Node>> Children;
        
        public:
            Node(const std::string NodeName) : Name(NodeName) {}
            virtual ~Node() = default;

            void AddChild(std::shared_ptr<Node> Child) {
                if (Child) {
                    Child->Parent = shared_from_this();
                    Children.push_back(Child);
                }
            }

            virtual void Update(float DeltaTime) {
                for (auto& child : Children) {
                    child->Update(DeltaTime);
                }
            }

            virtual void Draw() {
                for (auto& child : Children) {
                    child->Draw();
                }
            }

            const std::string& GetName() const {return Name;}
            std::shared_ptr<Node> GetParent() const {return Parent.lock();}
    };
}