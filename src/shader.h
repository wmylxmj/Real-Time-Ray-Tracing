//
// Created by wmy on 2023/12/15.
//

#ifndef RTRT_SHADER_H
#define RTRT_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    GLuint glID;

    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVec2(const std::string &name, const glm::vec2 &value) const;
    void SetVec3(const std::string &name, const glm::vec3 &value) const;
    void SetVec4(const std::string &name, const glm::vec4 &value) const;
    void SetMat2(const std::string &name, const glm::mat2 &mat) const;
    void SetMat3(const std::string &name, const glm::mat3 &mat) const;
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;
};

class VertexShader : public Shader {
public:
    explicit VertexShader(const char* pFile);
    ~VertexShader();
};

class FragmentShader : public Shader {
public:
    explicit FragmentShader(const char* pFile);
    ~FragmentShader();
};

class ShaderProgram : public Shader{
public:
    ShaderProgram(const char *pVertexShaderFile, const char *pFragmentShaderFile);
};

#endif //RTRT_SHADER_H
