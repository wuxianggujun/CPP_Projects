
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Canvas.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void error_callback(int error, const char *description) {
    fputs(description, stderr);
}


// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// Rect.hpp
class Rect : public Shape {
private:
    SkRect skRect;
public:
    Rect(float x, float y, float w, float h) {
        skRect = {x, y, w, h};
    }

    void draw(Canvas *canvas) override {
        canvas->drawRect(skRect, canvas->getPaint());
    }
};


int main() {
    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    Canvas canvas(WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Rect rect(100, 200, 200, 300);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        canvas.clear(SK_ColorWHITE);
        canvas.draw(&rect);
        canvas.flush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}