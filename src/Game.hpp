#pragma once 

#include <cassert>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SpriteSheet.hpp"
#include "TextureWrapper.hpp"

class Game {
public:
    explicit Game(int screenWidth, int screenHeight, const SpriteSheet& spriteSheet);

private:
    const int screenWidth;
    const int screenHeight;
    const SpriteSheet& spriteSheet;
    SDL_Window* windowPtr;
    SDL_Renderer* rendererPtr;
    std::vector<SDL_Rect> spriteClips;
    TextureWrapper spriteSheetTexture;
 
    void init();
    void loadMedia();
    void play();
    void close();
};

