#pragma once

#include "Objects/Object3D.hpp"
#include "Penumbra/PModel.hpp"
#include "Penumbra/PShader.hpp"
#include "Penumbra/PContext.hpp"
#include "Tools/Asset.hpp"

namespace Engine {
    class Model3D : public Object3D {
        public:
            std::string ModelID;
            std::string ShaderID;

            inline Model3D(const std::string& name, const std::string& model, const std::string& shader)
                : Object3D(name), ModelID(model), ShaderID(shader) {}
            
            inline void Render(RendererContext* context) {
                Shader& shader = Assets::Shaders.Get(ShaderID);
                Model& model = Assets::Models.Get(ModelID);

                shader.Bind();
                model.Bind();

                Material& material = Assets::Materials.Get(model.GetMaterialID());

                shader.SetVec4("material.ALBEDO", material.Albedo);
                shader.SetFloat("material.Specular", material.Specular);
                shader.SetInt("material.Shininess", material.Shininess);

                shader.SetMat4("model", transform.GetModelMatrix());

                context->DrawIndexed(Assets::Meshes.Get(model.GetMeshID()).GetIndexCount());
            }
    };
}
