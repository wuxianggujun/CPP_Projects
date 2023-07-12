#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkSurface.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

GrDirectContext *grDirectContext = nullptr;
SkSurface *skSurface = nullptr;

void init_Skia(int width, int height) {
    auto interface = GrGLMakeNativeInterface();
    grDirectContext = GrDirectContext::MakeGL(interface).release();

    GrGLFramebufferInfo framebufferInfo;
    framebufferInfo.fFBOID = 0;
    framebufferInfo.fFormat = GL_RGBA8;

    SkColorType colorType = kRGBA_8888_SkColorType;
    GrBackendRenderTarget backendRenderTarget(width, height, 0, 0, framebufferInfo);
    skSurface = SkSurface::MakeFromBackendRenderTarget(grDirectContext, backendRenderTarget,
                                                       kBottomLeft_GrSurfaceOrigin, colorType,
                                                       nullptr, nullptr).release();
    if (skSurface == nullptr) abort();

}

void clearnup_skia() {
    delete skSurface;
    delete grDirectContext;
}

// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

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

    init_Skia(WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    SkCanvas *canvas = skSurface->getCanvas();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        SkPaint paint;
        paint.setColor(SK_ColorWHITE);
        canvas->drawPaint(paint);
        paint.setColor(SK_ColorBLUE);
        canvas->drawRect({100, 200, 300, 500}, paint);
        canvas->flush();
        grDirectContext->flushAndSubmit();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    clearnup_skia();
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