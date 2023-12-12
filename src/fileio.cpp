//
// Created by wmy on 2023/12/12.
//

#include "fileio.h"

void SceneProcessing(const aiScene* scene);
void NodeProcessing(aiNode* node, const aiScene* scene);

bool ImportModel(const std::string& pFile) {
    Assimp::Importer importer;
    unsigned int pFlag = aiProcess_CalcTangentSpace       |
                         aiProcess_Triangulate            |
                         aiProcess_JoinIdenticalVertices  |
                         aiProcess_SortByPType;

    const aiScene* scene = importer.ReadFile(pFile, pFlag);

    if (scene == nullptr) {
        std::cout << importer.GetErrorString() << std::endl;
        return false;
    }

    SceneProcessing(scene);

    return true;
}

void SceneProcessing(const aiScene* scene) {
    NodeProcessing(scene->mRootNode, scene);
}

void NodeProcessing(aiNode* node, const aiScene* scene) {

}