//
// Created by wmy on 2023/12/16.
//

#include "camera.h"

void Camera::RotateXY(float dThetaX, float dThetaY) {
    float x = glm::sin(_gazeAngle.x);
    float z = - glm::cos(_gazeAngle.y);
    glm::mat4 rot = glm::mat4(1.0f);
    rot = glm::rotate(rot, dThetaY, glm::vec3(z, 0, x));
    rot = glm::rotate(rot, dThetaX, glm::vec3(0, 1, 0));
    _coordinateSystem = rot * _coordinateSystem;
}

glm::mat4 Camera::GetCameraMatrix() {
    return glm::lookAt(eyePosition, eyePosition + GetFrontDirection(), GetUpDirection());
}

glm::mat4 Camera::GetPerspectiveMatrix() {
    return glm::perspective(fovy, aspect, zNear, zFar);
}

glm::vec3 Camera::GetFrontDirection() {
    return - glm::vec3(glm::transpose(_coordinateSystem)[2]);
}

glm::vec3 Camera::GetUpDirection() {
    return glm::vec3(glm::transpose(_coordinateSystem)[1]);
}

glm::vec3 Camera::GetRightDirection() {
    return glm::vec3(glm::transpose(_coordinateSystem)[0]);
}
