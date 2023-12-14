//
// Created by wmy on 2023/12/12.
//

#ifndef RTRT_FILEIO_H
#define RTRT_FILEIO_H

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <glad/glad.h>
#include <vector>

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
} Vertex;

typedef struct {
    GLuint id;
    aiTextureType type;
    std::string pFile;
} Texture;

class Model {
private:
    std::string _directory;
    std::vector<Texture> _textures;

    void SceneProcessing(const aiScene* scene);
    void NodeProcessing(aiNode* node, const aiScene* scene);
    void MeshProcessing(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType textureType);

public:
    explicit Model(std::string pFile);

};

#endif //RTRT_FILEIO_H
