#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeChanged(GLFWwindow *glfwWindow, int width, int height);
void processInput(GLFWwindow *glfwWindow);

int main() {
    //初始化glfw
    if (!glfwInit()) {
        return -1;
    }

    //创建窗口
    GLFWwindow *glfwWindow = glfwCreateWindow(640, 480, "glfw_window", NULL, NULL);
    if (!glfwWindow) {
        glfwTerminate();
        return -1;
    }

    //将当前的context关联到glfwWindow
    glfwMakeContextCurrent(glfwWindow);
    glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeChanged);

    //glad需要要在glfwMakeContextCurrent后才能初始化
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    //消息循环
    while(!glfwWindowShouldClose(glfwWindow)) {
        processInput(glfwWindow);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 0, 1.0);
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebufferSizeChanged(GLFWwindow *glfwWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *glfwWindow) {
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(glfwWindow, true);
    }
}