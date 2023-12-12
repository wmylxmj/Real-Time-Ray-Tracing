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

extern bool ImportModel(const std::string& pFile);

#endif //RTRT_FILEIO_H
