#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include "fileio.h"
#include "camera.h"
#include "shader.h"

#define WINDOW_WIDTH_INIT 1920
#define WINDOW_HEIGHT_INIT 1080
#define MOUSE_SENSITIVITY 0.1f
#define CAMERA_MOVE_SPEED 2.5f

Camera camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void MouseMoveCallback(GLFWwindow* window, double x, double y) {
    static bool firstIn = true;
    static float lastX = WINDOW_WIDTH_INIT / 2.0;
    static float lastY = WINDOW_HEIGHT_INIT / 2.0;
    float xPos = static_cast<float>(x);
    float yPos = static_cast<float>(y);
    if (firstIn) {
        lastX = xPos;
        lastY = yPos;
        firstIn = false;
    }
    float dx = xPos - lastX;
    float dy = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.RotateXY(MOUSE_SENSITIVITY * dx, MOUSE_SENSITIVITY * dy);
}

void KeyboardInputProcessing(GLFWwindow *glfwWindow) {
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(glfwWindow, true);
    }

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera.eyePosition += deltaTime * CAMERA_MOVE_SPEED * camera.GetFrontDirection();
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera.eyePosition -= deltaTime * CAMERA_MOVE_SPEED * camera.GetFrontDirection();
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera.eyePosition -= deltaTime * CAMERA_MOVE_SPEED * camera.GetRightDirection();
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera.eyePosition += deltaTime * CAMERA_MOVE_SPEED * camera.GetRightDirection();
}

void WindowResizeCallback(GLFWwindow *glfwWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *glfwWindow = glfwCreateWindow(WINDOW_WIDTH_INIT, WINDOW_HEIGHT_INIT, "window", nullptr, nullptr);
    if (!glfwWindow) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSetFramebufferSizeCallback(glfwWindow, WindowResizeCallback);
    glfwSetCursorPosCallback(glfwWindow, MouseMoveCallback);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    Model model(R"(G:\LearnOpenGL-master\LearnOpenGL-master\resources\objects\backpack\backpack.obj)");
    ShaderProgram shader(R"(G:\RTRT\src\vertexShader.glsl)", R"(G:\RTRT\src\fragmentShader.glsl)");

    //消息循环
    while(!glfwWindowShouldClose(glfwWindow)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        KeyboardInputProcessing(glfwWindow);
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader.glID);
        shader.SetMat4("matPerspective", camera.GetPerspectiveMatrix());
        shader.SetMat4("matCamera", camera.GetCameraMatrix());

        // render the loaded model
        glm::mat4 matModel = glm::mat4(1.0f);
        matModel = glm::translate(matModel, glm::vec3(0.0f, 0.0f, 0.0f));
        matModel = glm::scale(matModel, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.SetMat4("matModel", matModel);
        model.draw(shader);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
