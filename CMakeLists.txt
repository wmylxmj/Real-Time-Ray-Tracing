cmake_minimum_required(VERSION 3.26)
project(RTRT)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTRT src/main.cpp
        src/fileio.cpp
        src/fileio.h)

find_package(glad CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE glm::glm)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE assimp::assimp)