//
// Created by wmy on 2023/12/14.
//

#ifndef RTRT_MESH_H
#define RTRT_MESH_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
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

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    GLuint VAO;

private:
    GLuint VBO, EBO;
    void setupGL();
};

#endif //RTRT_MESH_H
