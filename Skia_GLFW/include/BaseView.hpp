//
// Created by WuXiangGuJun on 2023/7/16.
//
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Canvas.hpp"
#include "Paint.hpp"

class BaseView {
public:
    BaseView(int width, int height, const char *title);

    ~BaseView();

    void onSizeChanged(int width, int height);

    void run();

    Canvas *getCanvas();

    Paint *getPaint();

protected:
    GLFWwindow *window;
    GrDirectContext *grDirectContext;
    SkSurface *skSurface;

private:
    void initGLFW();
    void initSkia();
    void resize(int width, int heigth);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
