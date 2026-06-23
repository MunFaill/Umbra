#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <cassert>
#include <utility>

#include "Renderer/RendererMesh.hpp"
#include "Renderer/RendererShader.hpp"
#include "Renderer/RendererTexture.hpp"

namespace Engine {
    template <typename T>
    class AssetManager {
        public:
            AssetManager() = default;
            ~AssetManager() = default;

            AssetManager(const AssetManager&) = delete;
            AssetManager& operator=(const AssetManager&) = delete;

            template <typename... Args>
            T& Load(const std::string& ID, Args&&... args) {
                auto it = m_Assets.find(ID);
                if (it != m_Assets.end()) {
                    return *(it->second);
                }

                auto asset = std::make_unique<T>(std::forward<Args>(args)...);
                auto& assetRef = *asset;

                m_Assets[ID] = std::move(asset);
                return assetRef;
            }

            T& Get(const std::string& ID) {
                auto it = m_Assets.find(ID);
                assert(it != m_Assets.end() && "Error: Asset not found");
                return *(it->second);
            }

            void Unload(const std::string& ID) {
                auto it = m_Assets.find(ID);
                if (it != m_Assets.end()) {
                    m_Assets.erase(it);
                }
            }
            
            void Clear() {
                m_Assets.clear();
            }

        private:
            std::unordered_map<std::string, std::unique_ptr<T>> m_Assets;
    };

    struct Assets {
        inline static AssetManager<Mesh> MeshManager;
        inline static AssetManager<Shader> ShaderManager;
        inline static AssetManager<Texture> TextureManager;
    };
}