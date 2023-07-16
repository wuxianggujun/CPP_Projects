//
// Created by WuXiangGuJun on 2023/7/16.
//
#include "BaseView.hpp"

BaseView::BaseView(int width, int height,const char* title) {
    initGLFW();
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    initSkia();
}

BaseView::~BaseView() {
    delete skSurface;
    delete grDirectContext;

    glfwDestroyWindow(window);
    glfwTerminate();
}

void BaseView::initGLFW() {
    glfwInit();

}

void BaseView::initSkia() {

}

