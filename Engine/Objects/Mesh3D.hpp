#pragma once

#include "Objects/Object3D.hpp"
#include "Penumbra/PMesh.hpp"
#include "Penumbra/PShader.hpp"
#include "Penumbra/PContext.hpp"
#include "Tools/Asset.hpp"

namespace Engine {
    class Mesh3D : public Object3D {
        public:
            std::string MeshID;
            std::string ShaderID;

            inline Mesh3D(const std::string& name, const std::string& mesh, const std::string& shader)
                : Object3D(name), MeshID(mesh), ShaderID(shader) {}
            
            inline void Render(RendererContext* context) {
                Shader& shader = Assets::Shaders.Get(ShaderID);
                Mesh& mesh = Assets::Meshes.Get(MeshID);

                shader.Bind();
                mesh.Bind();

                shader.SetMat4("model", transform.GetModelMatrix());

                context->DrawIndexed(mesh.GetIndexCount());
            }
    };
}
