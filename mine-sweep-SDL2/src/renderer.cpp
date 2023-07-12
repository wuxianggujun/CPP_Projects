//
// Created by WuXiangGuJun on 2023/7/11.
//
#include "renderer.hpp"

Renderer::Renderer(const Window &window) : renderer_(SDL_CreateRenderer(window.window_.get(), -1, 0), RendererDestroy) {

}

void Renderer::SetColor(const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer_.get(), color.r, color.g, color.b, color.a);
}

void Renderer::Clear() {
    SDL_RenderClear(renderer_.get());
}

void Renderer::Present() {
    SDL_RenderPresent(renderer_.get());
}

void Renderer::DrawRect(const SDL_Rect &rect) {
    SDL_RenderDrawRect(renderer_.get(), &rect);
}

void Renderer::FillRect(const SDL_Rect &rect) {
    SDL_RenderFillRect(renderer_.get(), &rect);
}

void Renderer::DrawLine(const SDL_Point &point1, const SDL_Point &point2) {
    SDL_RenderDrawLine(renderer_.get(), point1.x, point1.y, point2.x, point2.y);
}

void Renderer::DrawTexture(SDL_Texture *texture, const SDL_Rect &rect, int x, int y) {
    SDL_Rect dst = {x, y, rect.w, rect.h};
    SDL_RenderCopy(renderer_.get(), texture, &rect, &dst);
}
