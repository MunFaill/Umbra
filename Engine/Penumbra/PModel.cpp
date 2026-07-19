#include "Penumbra/PModel.hpp"

#include "Penumbra/PMesh.hpp"
#include "Penumbra/PBuffers.hpp"
#include "Tools/Asset.hpp"
#include "Tools/Log.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <vector>
#include <memory>

namespace Engine {
    void Model::LoadMesh(const std::string& MeshID) {
        m_MeshID = MeshID;
    }

    void Model::LoadMeshFromFile(const std::string& FilePath) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, FilePath.c_str())) {
            Print(Error, "OBJ loader error: {} OBJ loader warn: {}", err, warn);
            return;
        }

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (const tinyobj::shape_t& shape : shapes) {
            for (const tinyobj::index_t& index : shape.mesh.indices) {
                Vertex vertex{};

                vertex.Position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };

                if (index.texcoord_index >= 0) {
                    vertex.UV = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        attrib.texcoords[2 * index.texcoord_index + 1]
                    };
                }

                // 3. Normais (nx, ny, nz)
                if (index.normal_index >= 0) {
                    vertex.Normals = {
                        attrib.normals[3 * index.normal_index + 0],
                        attrib.normals[3 * index.normal_index + 1],
                        attrib.normals[3 * index.normal_index + 2]
                    };
                }
                
                // 4. Cores por vértice (r, g, b) - se existirem no obj
                if (!attrib.colors.empty()) {
                    vertex.Colors = {
                        attrib.colors[3 * index.vertex_index + 0],
                        attrib.colors[3 * index.vertex_index + 1],
                        attrib.colors[3 * index.vertex_index + 2],
                        1.0f // Alpha padrão
                    };
                }

                vertices.push_back(vertex);
                indices.push_back(indices.size());
            }
        }

        std::unique_ptr<VertexBuffer> i_Vertex = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex));
        std::unique_ptr<IndexBuffer> i_Index = IndexBuffer::Create(indices.data(), indices.size());

        Mesh& i_Mesh = Assets::Meshes.Add(FilePath, Mesh::Create(std::move(i_Vertex), std::move(i_Index)));
        m_MeshID = FilePath;
    }

    void Model::SetMaterial(const std::string& MaterialID) {
        m_MaterialID = MaterialID;
    }

    void Model::Bind() {
        if (!m_MeshID.empty()) {
            Assets::Meshes.Get(m_MeshID).Bind();
        }

        if (!m_MaterialID.empty()) {
            Material& material = Assets::Materials.Get(m_MaterialID);
            Assets::Textures.Get(material.TextureID).Bind();
        }
    }

    void Model::Unbind() {
        if (!m_MeshID.empty()) {
            Assets::Meshes.Get(m_MeshID).Unbind();
        }
    }
}