#pragma once

#include "Renderer/RendererMesh.hpp"
#include "Renderer/RendererShader.hpp"

#include <unordered_map>
#include <memory>
#include <string>
#include <utility>

namespace Engine {
    template<typename T>
    class AssetManager {
        public:
            AssetManager() = default;
            ~AssetManager() = default;

            AssetManager(const AssetManager&) = delete;
            AssetManager& operator=(const AssetManager&) = delete;

            template <typename... Args>
            T& Load(const std::string ID, Args&&... args) {
                auto It = m_Assets.find(ID);
                if (It != m_Assets.end()) {
                    return *(It->second);
                }

                auto Asset = std::make_unique<T>(std::forward<Args>(args)...);
                auto& AssetRef = *Asset;

                m_Assets[ID] = std::move(Asset);
                return AssetRef;
            }

            T& Add(const std::string& ID, std::unique_ptr<T> asset) {
                auto It = m_Assets.find(ID);
                if (It != m_Assets.end()) {
                    return *(It->second);
                }

                m_Assets[ID] = std::move(asset);
                return *(m_Assets[ID]);
            }

            T& Get(const std::string& ID) {
                auto It = m_Assets.find(ID);
                assert(It != m_Assets.end() && "Error: Asset not found");
                return *(It->second);
            }

            void Unload(const std::string& ID) {
                auto It = m_Assets.find(ID);
                if (It != m_Assets.end()) {
                    m_Assets.erase(It);
                }
            }

            void UnloadAll() {
                m_Assets.clear();
            }

        private:
            std::unordered_map<std::string, std::unique_ptr<T>> m_Assets;
    };

    struct Assets {
        inline static AssetManager<Mesh> Meshes;
        inline static AssetManager<Shader> Shaders;
    };

}