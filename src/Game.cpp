#include "Game.hpp"

#include <cassert>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SpriteSheet.hpp"
#include "TextureWrapper.hpp"

Game::Game(int screenWidth, int screenHeight, const SpriteSheet& spriteSheet) :
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    spriteSheet(spriteSheet),
    spriteClips(spriteSheet.frameCnt)
{
    init();
    loadMedia();
    play();
    close();
}

void Game::init() {
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    assert(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"));
    windowPtr = SDL_CreateWindow("Тестовое задание", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, screenWidth,
                                 screenHeight, SDL_WINDOW_SHOWN);
    rendererPtr = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED |
                                     SDL_RENDERER_PRESENTVSYNC);
    assert(windowPtr != nullptr);
    assert(rendererPtr != nullptr);
    assert(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG);
}

void Game::loadMedia() {
    assert(spriteSheetTexture.loadImageFromFile(rendererPtr, spriteSheet.pathTo));
    const auto frameCnt = spriteSheet.frameCnt;
    const auto frameWidth = spriteSheet.frameWidth;
    const auto totalHeight = spriteSheet.totalHeight;
    for (int i = 0; i < frameCnt; ++i) {
        spriteClips[i].x = i * frameWidth;
        spriteClips[i].y = 0;
        spriteClips[i].w = frameWidth;
        spriteClips[i].h = totalHeight; 
    }

}

void Game::play() {
    bool quit = false;
    SDL_Event eventHandler;
    int currentFrame = 0;
    int totalFrameCnt = spriteSheet.frameCnt;
    while (!quit) {
        while (SDL_PollEvent(&eventHandler)) {
            if (eventHandler.type == SDL_QUIT)
                quit = true;
        }
        SDL_SetRenderDrawColor(rendererPtr, 255, 255, 255, 255);
        SDL_RenderClear(rendererPtr);
        auto currentClip = &spriteClips[currentFrame / totalFrameCnt];
        spriteSheetTexture.render(rendererPtr, currentClip,
                                  (screenWidth - currentClip->w) / 2,
                                  (screenHeight - currentClip->h) / 2);
        SDL_RenderPresent(rendererPtr);
        ++currentFrame;
        if (currentFrame / totalFrameCnt >= totalFrameCnt)
            currentFrame = 0;
    }
}

void Game::close() {
    spriteSheetTexture.free();
    SDL_DestroyRenderer(rendererPtr);
    SDL_DestroyWindow(windowPtr);
    rendererPtr = nullptr;
    windowPtr = nullptr;
    IMG_Quit();
    SDL_Quit();
}