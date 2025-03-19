#include "Reel.hpp"

#include <cassert>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Utils.hpp"

/* --- static --- */
const int Reel::width = 100;
const int Reel::height = 300;
const int Reel::symbolSize = 100;
bool Reel::imagesLoaded = false;
std::vector<SDL_Texture*> Reel::symbolTextures;
const std::vector<std::string> Reel::imagePaths = {
    "assets/circle.png",
    "assets/gold.png",
    "assets/heart.png",
    "assets/rhombus.png",
    "assets/spade.png",
    "assets/square.png",
    "assets/star.png",
    "assets/triangle.png"
};
/* -------------- */

Reel::Reel(int x, int y, SDL_Renderer* renderer) :
    isSpinning(false),
    x(x),
    y(y),
    renderer(renderer)
{
    for (int i = 0; i < 8; ++i) {
        if (i == 1) // gold
            continue;
        if (i == 7) // triangle
            continue;
        for (int _ = 0; _ < 3; ++_)
            symbols.push_back(i);
    }

    utils::shuffleVector(symbols);
    symbols.insert(symbols.begin() + 1, 7); // starting with triangle
    symbols.push_back(1);
    currentSymbolIdx = symbols[1];
    if (!imagesLoaded) {
        loadImages();
        imagesLoaded = true;
    }
}

void Reel::update() {
    if (!isSpinning)
        return;
    int lastSymbol = symbols.back();
    for (size_t i = symbols.size() - 1; i > 0; --i)
        symbols[i] = symbols[i - 1];
    symbols[0] = lastSymbol;
    currentSymbolIdx = symbols[1];
}

void Reel::render() {
    for (int i = 0; i < 3; ++i) {
        SDL_Rect imgRect = { x, y + i * symbolSize, symbolSize, symbolSize };
        SDL_RenderCopy(renderer, symbolTextures[symbols[i]], nullptr,
                       &imgRect);
    }
}

int Reel::getCurrentSymbolIdx() {
    return currentSymbolIdx;
}

void Reel::loadImages() {
    for (const auto& path : imagePaths) {
        SDL_Surface* tmpSurface = IMG_Load(path.c_str());
        assert(tmpSurface != nullptr);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,
                                                            tmpSurface);
        SDL_FreeSurface(tmpSurface);
        assert(texture != nullptr);
        symbolTextures.push_back(texture);
    }
}

void Reel::destroyTextures() {
    for (auto& texture : symbolTextures)
        SDL_DestroyTexture(texture);
}
