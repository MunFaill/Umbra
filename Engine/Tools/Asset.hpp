#pragma once

#include "Tools/Log.hpp"

#include "Penumbra/PMesh.hpp"
#include "Penumbra/PShader.hpp"
#include "Penumbra/PTexture.hpp"

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

            T& Add(const std::string& ID, std::unique_ptr<T> asset) {
                auto It = m_Assets.find(ID);
                if (It != m_Assets.end()) {
                    return *(It->second);
                }

                m_Assets[ID] = std::move(asset);

                Print(Message, "New asset added: {}", ID);

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

                Print(Message, "Asset unloaded: {}", ID);
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
        inline static AssetManager<Texture> Textures;
    };

}
