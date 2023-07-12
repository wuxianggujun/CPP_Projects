//
// Created by WuXiangGuJun on 2023/7/11.
//
#pragma once


#include "pch.hpp"

inline auto WindowDestroy = [](SDL_Window *window) {
    SDL_DestroyWindow(window);
};

class Window final {
public:
    friend class Renderer;

    Window(const std::string &title, int width, int height);

private:
    std::unique_ptr<SDL_Window, decltype(WindowDestroy)> window_;

};