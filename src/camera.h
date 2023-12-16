//
// Created by wmy on 2023/12/16.
//

#ifndef RTRT_CAMERA_H
#define RTRT_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 _gazeAngle = glm::vec3(0, 0, 0);
    glm::mat4 _coordinateSystem = glm::mat4(1.0f);

public:
    glm::vec3 eyePosition = glm::vec3(0, 0, 0);
    float fovy = glm::radians(60.0f);
    float aspect = 16.0 / 9;
    float zNear = 0.1f;
    float zFar = 100.0f;

    glm::mat4 GetPerspectiveMatrix();
    glm::mat4 GetCameraMatrix();
    void RotateXY(float dThetaX, float dThetaY);
    glm::vec3 GetFrontDirection();
    glm::vec3 GetUpDirection();
    glm::vec3 GetRightDirection();
};


#endif //RTRT_CAMERA_H
