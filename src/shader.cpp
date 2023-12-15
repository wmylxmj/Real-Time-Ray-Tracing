//
// Created by wmy on 2023/12/15.
//

#include "shader.h"

VertexShader::VertexShader(const char *pFile) {
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(pFile);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << e.what() << std::endl;
    }
    glID = glCreateShader(GL_VERTEX_SHADER);
    const char* shaderCode = code.c_str();
    glShaderSource(glID, 1, &shaderCode, nullptr);
    glCompileShader(glID);

    GLint success;
    glGetShaderiv(glID, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(glID, 1024, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}

VertexShader::~VertexShader() {
    glDeleteShader(glID);
}

FragmentShader::FragmentShader(const char *pFile) {
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(pFile);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << e.what() << std::endl;
    }
    glID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* shaderCode = code.c_str();
    glShaderSource(glID, 1, &shaderCode, nullptr);
    glCompileShader(glID);

    GLint success;
    glGetShaderiv(glID, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(glID, 1024, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}

FragmentShader::~FragmentShader() {
    glDeleteShader(glID);
}

Shader::Shader(const char *pVertexShaderFile, const char *pFragmentShaderFile) {
    VertexShader vertexShader(pVertexShaderFile);
    FragmentShader fragmentShader(pFragmentShaderFile);
    glID = glCreateProgram();
    glAttachShader(glID, vertexShader.glID);
    glAttachShader(glID, fragmentShader.glID);
    glLinkProgram(glID);

    GLint success;
    glGetProgramiv(glID, GL_LINK_STATUS, &success);
    if(!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(glID, 1024, nullptr, infoLog);
        std::cout << infoLog << std::endl;
    }
}
