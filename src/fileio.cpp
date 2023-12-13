//
// Created by wmy on 2023/12/12.
//

#include "fileio.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void SceneProcessing(const aiScene* scene);
void NodeProcessing(aiNode* node, const aiScene* scene);
void MeshProcessing(aiMesh* mesh, const aiScene* scene);
std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType textureType);

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
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        MeshProcessing(mesh, scene);
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        NodeProcessing(node->mChildren[i], scene);
    }
}

void MeshProcessing(aiMesh* mesh, const aiScene* scene) {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
    //std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
    //std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT);
    //std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT);
}

GLuint LoadTexture(const char* pFile) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nChannels;
    stbi_uc* image = stbi_load(pFile, &width, &height, &nChannels, 0);

    if (image) {
        GLenum format;
        if (nChannels == 1) format = GL_RED;
        else if (nChannels == 3) format = GL_RGB;
        else if (nChannels == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::cout << "Loaded texture: " << pFile << std::endl;
    }
    else {
        std::cout << "Cannot load texture: " << pFile << std::endl;
    }

    stbi_image_free(image);

    return textureID;
}

std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType textureType) {
    std::vector<Texture> textures;
    std::vector<Texture> texturesLoaded;
    for(unsigned int i = 0; i < material->GetTextureCount(textureType); i++) {
        aiString path;
        material->GetTexture(textureType, i, &path);
        bool loaded = false;
        for (auto & j : texturesLoaded) {
            if(std::strcmp(j.pFile.data(), path.C_Str()) == 0)
            {
                textures.push_back(j);
                loaded = true;
                break;
            }
        }
        if (!loaded) {
            Texture texture;
            texture.id = LoadTexture(path.C_Str());
            texture.type = textureType;
            texture.pFile = path.C_Str();
            textures.push_back(texture);
            texturesLoaded.push_back(texture);
        }
    }
    return textures;
}