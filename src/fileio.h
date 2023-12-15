//
// Created by wmy on 2023/12/12.
//

#ifndef RTRT_FILEIO_H
#define RTRT_FILEIO_H

#include <iostream>
#include <vector>
#include "mesh.h"

class Model {
private:
    std::string _directory;
    std::vector<Texture> _textures;

    void SceneProcessing(const aiScene* scene);
    void NodeProcessing(aiNode* node, const aiScene* scene);
    void MeshProcessing(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType textureType);

public:
    std::vector<Mesh> meshes;

    explicit Model(std::string pFile);
    void draw(const Shader& shader);
};

#endif //RTRT_FILEIO_H
