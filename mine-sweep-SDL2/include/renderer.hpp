//
// Created by WuXiangGuJun on 2023/7/11.
//
#pragma once

#include "window.hpp"

inline auto RendererDestroy = [](SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
};


class Renderer final {
public:
    friend struct Context;

    Renderer(const Window &window);


    void SetColor(const SDL_Color &color);

    void Clear();

    void Present();

    void DrawRect(const SDL_Rect& rect);
    void FillRect(const SDL_Rect& rect);
    void DrawLine(const SDL_Point& point1, const SDL_Point& point2);
    void DrawTexture(SDL_Texture* texture,const SDL_Rect& rect,int x,int y);



private:
    std::unique_ptr<SDL_Renderer, decltype(RendererDestroy)> renderer_;

};