#include "Text.hpp"

#include <cassert>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

Text::Text(const int x, const int y, const int w, const int h) :
    x(x),
    y(y),
    width(w),
    height(h),
    textureLoaded(false),
    fontLoaded(false)
{}

void Text::render(SDL_Renderer* renderer, const std::string text) {
    if (!fontLoaded) {
        font = TTF_OpenFont("assets/Arial.ttf", 30);
        assert(font != nullptr);
        fontLoaded = true;
    }
    if (textureLoaded) {
        SDL_DestroyTexture(texture);
        textureLoaded = false;
    }
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(),
                                                    textColor);
    assert(textSurface != nullptr);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    textureLoaded = true;
    SDL_Rect textRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);
}

Text::~Text()
{
    if (textureLoaded)
        SDL_DestroyTexture(texture);
}

void Text::closeFont() {
    TTF_CloseFont(font);
}
