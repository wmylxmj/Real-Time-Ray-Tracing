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

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
} Vertex;

typedef struct {
    GLuint id;
    std::string type;
    std::string pFile;
} Texture;

extern bool ImportModel(const std::string& pFile);

#endif //RTRT_FILEIO_H
