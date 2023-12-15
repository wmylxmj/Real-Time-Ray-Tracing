//
// Created by wmy on 2023/12/12.
//

#include "fileio.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Model::Model(std::string pFile) {
    Assimp::Importer importer;
    unsigned int pFlag = aiProcess_CalcTangentSpace |
                         aiProcess_Triangulate |
                         aiProcess_JoinIdenticalVertices |
                         aiProcess_SortByPType;

    const aiScene *scene = importer.ReadFile(pFile, pFlag);

    if (scene == nullptr) {
        std::cout << importer.GetErrorString() << std::endl;
        return;
    }

    std::replace(pFile.begin(), pFile.end(), '\\', '/');
    _directory = pFile.substr(0, pFile.find_last_of('/') + 1);

    SceneProcessing(scene);
}

void Model::SceneProcessing(const aiScene *scene) {
    NodeProcessing(scene->mRootNode, scene);
}

void Model::NodeProcessing(aiNode* node, const aiScene* scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        MeshProcessing(mesh, scene);
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        NodeProcessing(node->mChildren[i], scene);
    }
}

void Model::MeshProcessing(aiMesh* mesh, const aiScene* scene) {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        if (mesh->HasNormals()) {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }
        if (mesh->mTextureCoords[0]) {
            vertex.textureCoord.x = mesh->mTextureCoords[0][i].x;
            vertex.textureCoord.y = mesh->mTextureCoords[0][i].y;

            vertex.tangent.x = mesh->mTangents[i].x;
            vertex.tangent.y = mesh->mTangents[i].y;
            vertex.tangent.z = mesh->mTangents[i].z;

            vertex.bitangent.x = mesh->mBitangents[i].x;
            vertex.bitangent.y = mesh->mBitangents[i].y;
            vertex.bitangent.z = mesh->mBitangents[i].z;
        }
        else {
            vertex.textureCoord = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseTextures = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
    textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

    std::vector<Texture> specularTextures = LoadMaterialTextures(material, aiTextureType_SPECULAR);
    textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());

    std::vector<Texture> heightTextures = LoadMaterialTextures(material, aiTextureType_HEIGHT);
    textures.insert(textures.end(), heightTextures.begin(), heightTextures.end());

    std::vector<Texture> ambientTextures = LoadMaterialTextures(material, aiTextureType_AMBIENT);
    textures.insert(textures.end(), ambientTextures.begin(), ambientTextures.end());

    meshes.emplace_back(std::move(vertices), std::move(indices), std::move(textures));
}

GLuint LoadTexture(const char* pFile) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nChannels;
    stbi_uc* image = stbi_load(pFile, &width, &height, &nChannels, 0);

    if (image) {

        GLint format;
        if (nChannels == 1) format = GL_RED;
        else if (nChannels == 3) format = GL_RGB;
        else if (nChannels == 4) format = GL_RGBA;
        else {
            std::cout << "Unsupported pixel format: " << pFile << std::endl;
            stbi_image_free(image);
            return textureID;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::cout << "Texture loaded: " << pFile << std::endl;
    }
    else {
        std::cout << "Cannot load texture: " << pFile << std::endl;
    }

    stbi_image_free(image);

    return textureID;
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType textureType) {
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(textureType); i++) {
        aiString pTexture;
        material->GetTexture(textureType, i, &pTexture);
        bool loaded = false;
        for (Texture& textureLoaded : _textures) {
            if(std::strcmp(textureLoaded.pFile.data() + _directory.size(), pTexture.C_Str()) == 0)
            {
                textures.push_back(textureLoaded);
                loaded = true;
                break;
            }
        }
        if (!loaded) {
            Texture texture;
            texture.pFile = _directory + pTexture.C_Str();
            texture.glID = LoadTexture(texture.pFile.data());
            texture.type = textureType;
            textures.push_back(texture);
            _textures.push_back(texture);
        }
    }
    return textures;
}

void Model::draw(const Shader &shader) {
    for (Mesh & mesh : meshes) {
        mesh.draw(shader);
    }
}
