//
// Created by WuXiangGuJun on 2023/7/11.
//
#include "context.hpp"

constexpr SDL_Color NormalTileColor = {150, 150, 150, 255};
constexpr SDL_Color HoverlTileColor = {200, 200, 200, 255};
constexpr SDL_Color BorderTileColor = {0, 0, 0, 255};
constexpr SDL_Color NakedTileColor = {50, 50, 50, 255};
constexpr SDL_Color KeyColor = {118, 66, 138, 255};

std::unique_ptr<Context> Context::instance_ = nullptr;

Map CreateRandomMap(int bombCount, int width, int height) {
    SDL_assert(bombCount < width * height);

    std::random_device d;
    std::mt19937 gen(d());
    std::uniform_int_distribution dist1(0, width - 1);
    std::uniform_int_distribution dist2(0, height - 1);

    Map map(width, height);

    constexpr int MaxBombSetupCount = 100;

    while (bombCount > 0) {
        bool setupBomb = false;
        int setupCount = MaxBombSetupCount;

        while (!setupBomb && setupCount > 0) {
            int x = dist1(gen);
            int y = dist2(gen);

            auto &tile = map.Get(x, y);
            if (tile.type != Tile::Bomb) {
                tile.type = Tile::Bomb;
                setupBomb = true;
            } else {
                setupCount--;
            }
        }

        if (setupCount == 0) {
            for (int i = 0; i < map.MaxSize(); i++) {
                if (map.GetByIndex(i).type != Tile::Bomb) {
                    map.GetByIndex(i).type = Tile::Bomb;
                    break;
                }
            }
        }

        bombCount--;
    }
    //generate nearly mine number

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto &tile = map.Get(x, y);
            if (tile.type == Tile::Bomb) {
                continue;
            }

            int mineCount = 0;
            for (int nx = 0; nx < 1; ++nx) {
                for (int ny = 0; ny < 1; ++ny) {
                    int detectX = x + nx;
                    int detectY = y + ny;
                    if (map.IsIn(detectX, detectY)) {
                        if (map.Get(detectX, detectY).type == Tile::Bomb) {
                            mineCount++;
                        }
                    }
                }
            }
            tile.type = static_cast<Tile::Type>(mineCount);
        }
    }
    return map;
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &bmpFileName, const SDL_Color &keycolor) {
    SDL_Surface *surface = SDL_LoadBMP(bmpFileName.c_str());
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_RESERVED1, "%s load failed", bmpFileName.c_str());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, keycolor.r, keycolor.g, keycolor.b));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_RESERVED1, "texture crates from %s failed", bmpFileName.c_str());
    }
    SDL_FreeSurface(surface);
    return texture;
}

Context::Context(Window &&window, Renderer &&renderer, Map &&map, int mineCount)
        : numberImage(loadTexture(renderer.renderer_.get(), "resources/font.bmp", KeyColor), TextureDestroy),
          mineImage(loadTexture(renderer.renderer_.get(), "resources/mine.bmp", KeyColor), TextureDestroy),
          flagImage(loadTexture(renderer.renderer_.get(), "resources/flag.bmp", KeyColor), TextureDestroy),
          gameOverImage(loadTexture(renderer.renderer_.get(), "resources/gameover.bmp", KeyColor), TextureDestroy),
          winImage(loadTexture(renderer.renderer_.get(), "resources/win.bmp", KeyColor), TextureDestroy),
          window(std::move(window)),
          renderer(std::move(renderer)),
          map(std::move(map)),
          mineCount(mineCount) {}

void Context::DrawMap() {
    for (int y = 0; y < map.Height(); ++y) {
        for (int x = 0; x < map.Width(); ++x) {
            const auto &tile = map.Get(x, y);
            drawOneTile(x, y, tile);
        }
    }
    if (state == GameState::Explode) {
        renderer.DrawTexture(gameOverImage.get(), SDL_Rect{0, 0, 256, 256},
                             (WindowWidth - 256) / 2,
                             (WindowHeight - 256) / 2);
    }
    if (state == GameState::Win) {
        renderer.DrawTexture(winImage.get(), SDL_Rect{0, 0, 256, 256},
                             (WindowWidth - 256) / 2,
                             (WindowHeight - 256) / 2);
    }
}


void Context::drawOneTile(int x, int y, const Tile &tile) {
    int tileX = x * TileSize;
    int tileY = y * TileSize;
    SDL_Rect rect = {tileX, tileY, TileSize, TileSize};
    SDL_Point mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    if (SDL_PointInRect(&mousePos, &rect)) {
        renderer.SetColor(HoverlTileColor);
    } else {
        renderer.SetColor(NormalTileColor);
    }
    if (tile.isVisiable && static_cast<int>(tile.type) >= 0) {
        renderer.SetColor(NakedTileColor);
    }

    renderer.FillRect(rect);
    renderer.SetColor(BorderTileColor);
    renderer.DrawRect(rect);

    if (tile.isVisiable) {
        if (tile.type == Tile::Bomb) {
            renderer.DrawTexture(mineImage.get(), SDL_Rect{0, 0, 32, 32}, tileX, tileY);
        } else {
            int mineCount = tile.type;
            if (mineCount > 0) {
                renderer.DrawTexture(numberImage.get(), SDL_Rect{309 / 8 * (mineCount - 1), 0, 32, 32}, tileX, tileY);
            }
        }
    } else {
        if (tile.isFlaged) {
            renderer.DrawTexture(flagImage.get(), SDL_Rect{0, 0, 32, 32}, tileX, tileY);
        }
    }

    if (debugMode) {
        if (tile.type == Tile::Bomb) {
            renderer.DrawTexture(mineImage.get(), SDL_Rect{0, 0, 32, 32}, tileX, tileY);
        } else {
            int mineCount = tile.type;
            if (mineCount > 0) {
                renderer.DrawTexture(numberImage.get(), SDL_Rect{309 / 8 * (mineCount - 1), 0, 32, 32}, tileX, tileY);
            }
        }
    }

}

void Context::HandleEvent(SDL_Event &event) {
    if (!state == GameState::Gaming) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            map = CreateRandomMap(MineCount, WindowWidth / TileSize, WindowHeight / TileSize);
            mineCount = MineCount;
            nakkedCount = 0;
            state = GameState::Gaming;
        }
        return;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            handleMoudeLeftBtnDown(event.button);
        }
        if (event.button.button == SDL_BUTTON_RIGHT) {
            handleMoudeRightBtnDown(event.button);
        }
    }
    if (event.type == SDL_KEYDOWN) {
        handleKeyDown(event.key);
    }
}

inline SDL_Point calcTileCoord(int mouseX, int mouseY) {
    return {mouseX / TileSize, mouseY / TileSize};
}

void floodFill(Context &ctx, Map &map, int x, int y) {
    if (!map.IsIn(x, y)) {
        return;
    }

    auto &tile = map.Get(x, y);
    if (!tile.isVisiable && !tile.isFlaged && tile.type != Tile::Bomb) {
        tile.isVisiable = true;
        ctx.nakkedCount++;

        if (static_cast<int>(tile.type) == 0) {
            floodFill(ctx, map, x - 1, y);
            floodFill(ctx, map, x + 1, y);
            floodFill(ctx, map, x, y - 1);
            floodFill(ctx, map, x, y + 1);
        }
    }
}


void Context::handleMoudeLeftBtnDown(const SDL_MouseButtonEvent &mouseButtonEvent) {
    auto tileCoord = calcTileCoord(mouseButtonEvent.x, mouseButtonEvent.y);
    if (!map.IsIn(tileCoord.x, tileCoord.y)) {
        return;
    }
    auto &tile = map.Get(tileCoord.x, tileCoord.y);
    if (tile.isVisiable || tile.isFlaged) {
        return;
    }

    if (!tile.isVisiable && tile.type == Tile::Bomb) {
        state = GameState::Explode;
        for (int i = 0; i < map.MaxSize(); ++i) {
            auto &tile = map.GetByIndex(i);
            tile.isVisiable = true;
            tile.isFlaged = false;
        }
        return;
    }

    floodFill(*this, map, tileCoord.x, tileCoord.y);

    if (nakkedCount == map.MaxSize() - mineCount) {
        state = GameState::Win;
    }
}

void Context::handleMoudeRightBtnDown(const SDL_MouseButtonEvent &mouseButtonEvent) {
    auto tileCoord = calcTileCoord(mouseButtonEvent.x, mouseButtonEvent.y);
    if (!map.IsIn(tileCoord.x, tileCoord.y)) {
        return;
    }

    auto &tile = map.Get(tileCoord.x, tileCoord.y);

    if (!tile.isVisiable) {
        tile.isFlaged = !tile.isFlaged;
    }
}

void Context::handleKeyDown(const SDL_KeyboardEvent &keyboardEvent) {
    if (keyboardEvent.keysym.scancode == SDL_SCANCODE_G) {
        debugMode = !debugMode;
    }
}
