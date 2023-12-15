//
// Created by wmy on 2023/12/14.
//

#include "mesh.h"

void Mesh::setupGL() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(Vertex)), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(indices.size() * sizeof(GLuint)), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> &&vertices, std::vector<GLuint> &&indices, std::vector<Texture> &&textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupGL();
}

void Mesh::draw(const Shader &shader) {

    unsigned int nDiffuse = 1;
    unsigned int nSpecular = 1;
    unsigned int nHeight = 1;
    unsigned int nAmbient = 1;

    for (GLint i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string name;
        if(textures[i].type == aiTextureType_DIFFUSE)
            name = "textureDiffuse" + std::to_string(nDiffuse++);
        else if(textures[i].type == aiTextureType_SPECULAR)
            name = "textureSpecular" + std::to_string(nSpecular++);
        else if(textures[i].type == aiTextureType_HEIGHT)
            name = "textureHeight" + std::to_string(nHeight++);
        else if(textures[i].type == aiTextureType_AMBIENT)
            name = "textureAmbient" + std::to_string(nAmbient++);

        glUniform1i(glGetUniformLocation(shader.glID, name.c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].glID);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}
