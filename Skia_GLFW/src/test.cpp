
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Canvas.hpp"

size_t memory_usage = 0;

void *operator new(size_t size) {
    memory_usage += size;
    return malloc(size);
}

void operator delete(void *ptr) {
    free(ptr);
}

void printMemoryUsage() {
    std::cout << "Memory used: " << memory_usage << " bytes" << std::endl;
}

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
    SkRect skRect{};
public:
    Rect(float x, float y, float w, float h) {
        skRect = {x, y, w, h};
    }

    void draw(Canvas *canvas) override {
        canvas->drawRect(skRect, canvas->getPaint());
    }
};

class LineNumber : public Shape {

private:

    void draw(Canvas *canvas) override {
        float offsetX = 50;
        float offsetY = 40;

        for (int i = 1; i <= 10; i++) {

            float x = offsetX + 20;
            float y = offsetY + i * 30;

            canvas->getSkCanvas()->drawLine(offsetX, offsetX, x, y, getPaint());
        }
    }

public:
    LineNumber() {
        paint.setAntiAlias(true);
    }
};

int main() {
    printMemoryUsage();
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
    LineNumber lineNumber;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        canvas.clear(SK_ColorWHITE);
        canvas.draw(&lineNumber);
        canvas.flush();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    printMemoryUsage();
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