#pragma once

#include <cassert>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Utils.hpp"

class Reel {
public:
    explicit Reel(int x, int y, SDL_Renderer* renderer);
    ~Reel() = default;
    void update();
    void render();
    int getCurrentSymbolIdx();
    bool isSpinning;
    std::vector<int> symbols;

    static void destroyTextures();

private:
    static const int width;
    static const int height;
    static const int symbolSize;
    static bool imagesLoaded;
    int x; // non-const for default operator=
    int y;
    int currentSymbolIdx;
    SDL_Renderer* renderer;
    static std::vector<SDL_Texture*> symbolTextures;
    static const std::vector<std::string> imagePaths;

    void loadImages();
};
