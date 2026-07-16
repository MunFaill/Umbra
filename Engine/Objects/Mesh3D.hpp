#pragma once

#include "Objects/Object3D.hpp"
#include "Penumbra/PMesh.hpp"
#include "Penumbra/PShader.hpp"
#include "Penumbra/PTexture.hpp"
#include "Penumbra/PContext.hpp"
#include "Tools/Asset.hpp"

namespace Engine {
    class Mesh3D : public Object3D {
        public:
            std::string MeshID;
            std::string TextureID;
            std::string ShaderID;

            inline Mesh3D(const std::string& name, const std::string& mesh, const std::string& texture, const std::string& shader)
                : Object3D(name), MeshID(mesh), TextureID(texture), ShaderID(shader) {}
            
            inline void Render(RendererContext* context) {
                Shader& shader = Assets::Shaders.Get(ShaderID);
                Texture& texture = Assets::Textures.Get(TextureID);
                Mesh& mesh = Assets::Meshes.Get(MeshID);

                shader.Bind();
                texture.Bind();
                mesh.Bind();

                shader.SetMat4("model", transform.GetModelMatrix());

                context->DrawIndexed(mesh.GetIndexCount());
            }
    };
}
