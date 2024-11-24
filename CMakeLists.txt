cmake_minimum_required(VERSION 3.26)
project(RTRT)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTRT src/main.cpp
        src/fileio.cpp
        src/fileio.h
        src/mesh.cpp
        src/mesh.h
        src/shader.cpp
        src/shader.h
        src/camera.cpp
        src/camera.h
        src/bvh.cpp
        src/bvh.h
        src/obb.cpp
        src/obb.h
        src/sobol.cpp
        src/sobol.h
        lib/svpng.inc)

find_package(glad CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE glm::glm)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE assimp::assimp)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE Eigen3::Eigen)

find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")