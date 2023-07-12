//
// Created by WuXiangGuJun on 2023/7/11.
//
#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "matrix.hpp"

struct Tile {
    enum Type {
        Bomb = -1
    } type = static_cast<Type>(0);
    bool isVisiable = false;
    bool isFlaged = false;
};
constexpr int TileSize = 32;
constexpr int WindowWidth = TileSize * 20;
constexpr int WindowHeight = TileSize * 20;
constexpr int MineCount = 50;

using Map = Matrix<Tile>;

Map CreateRandomMap(int bombCount, int width, int height);

// 使用lambda表达式定义的内联函数，用于销毁SDL_Texture对象
inline auto TextureDestroy = [](SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
};

struct Context final {
    enum GameState {
        Gaming,
        Win,
        Explode
    };
    GameState state = Gaming;

    std::unique_ptr<SDL_Texture, decltype(TextureDestroy)> numberImage;
    std::unique_ptr<SDL_Texture, decltype(TextureDestroy)> mineImage;
    std::unique_ptr<SDL_Texture, decltype(TextureDestroy)> flagImage;
    std::unique_ptr<SDL_Texture, decltype(TextureDestroy)> gameOverImage;
    std::unique_ptr<SDL_Texture, decltype(TextureDestroy)> winImage;

    Window window;
    Renderer renderer;
    Map map;

    bool debugMode = false;
    int nakkedCount = 0;
    int mineCount = 0;
    SDL_Event event;
    bool shouldClose = false;

    static void Init() {
        if (!instance_) {
            Window window("Mine_Sweep", WindowWidth, WindowHeight);
            Renderer renderer(window);
            instance_ = std::unique_ptr<Context>(new Context(
                    std::move(window),
                    std::move(renderer),
                    CreateRandomMap(MineCount, WindowWidth / TileSize, WindowHeight / TileSize),
                    MineCount
            ));
        }
    }

    static void Quit() {
        instance_.reset();
    }

    // 获取游戏上下文实例
    static Context &Inst() {
        SDL_assert(instance_);
        return *instance_;
    }

    void DrawMap();

    void HandleEvent(SDL_Event &event);

private:
    static std::unique_ptr<Context> instance_;


    Context(Window &&window, Renderer &&renderer, Map &&map, int mineCount);

    void drawOneTile(int x, int y, const Tile &tile);

    void handleMoudeLeftBtnDown(const SDL_MouseButtonEvent &mouseButtonEvent);

    void handleMoudeRightBtnDown(const SDL_MouseButtonEvent &mouseButtonEvent);

    void handleKeyDown(const SDL_KeyboardEvent &keyboardEvent);
};
