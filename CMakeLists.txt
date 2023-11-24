cmake_minimum_required(VERSION 3.26)
project(RTRT)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTRT src/main.cpp)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
target_link_libraries(RTRT PRIVATE glad::glad)
target_link_libraries(RTRT PRIVATE glfw)
target_link_libraries(RTRT PRIVATE glm::glm)
