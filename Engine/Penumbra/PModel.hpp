#pragma once

#include <string>

namespace Engine {

    // Forward declaration
    class Mesh;
    struct Material;

    class Model {
        public:
            Model() = default;
            ~Model() = default;

            void LoadMesh(const std::string& MeshID);
            void SetMaterial(const std::string& MaterialID);
            void LoadMeshFromFile(const std::string& FilePath);

            void Bind();
            void Unbind();

            inline std::string GetMeshID() {return m_MeshID;}
            inline std::string GetMaterialID() {return m_MaterialID;}
        private:
            std::string m_MeshID;
            std::string m_MaterialID;
    };
}