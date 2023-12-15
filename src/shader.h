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

class VertexShader {
public:
    GLuint glID;
    explicit VertexShader(const char* pFile);
    ~VertexShader();
};

class FragmentShader {
public:
    GLuint glID;
    explicit FragmentShader(const char* pFile);
    ~FragmentShader();
};

class Shader {
public:
    GLuint glID;
    Shader(const char *pVertexShaderFile, const char *pFragmentShaderFile);
};

#endif //RTRT_SHADER_H
