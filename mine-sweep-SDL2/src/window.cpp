//
// Created by WuXiangGuJun on 2023/7/11.
//
#include "window.hpp"

Window::Window(const std::string &title, int width, int height) : window_(
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                         SDL_WINDOW_SHOWN), WindowDestroy) {
}
