#include "Button.hpp"

#include <cassert>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Button::Button(const int x, const int y, const int w, const int h) :
    x(x),
    y(y),
    width(w),
    height(h)
{}

Button::~Button() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Button::render(SDL_Renderer* renderer, std::string pathToImg) {
    SDL_Rect buttonRect = { x, y, width, height };
    if (!textureLoaded) {
        SDL_Surface* tmpSurface = IMG_Load(pathToImg.c_str());
        assert(tmpSurface != nullptr);
        texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        assert(texture != nullptr);
        textureLoaded = true;
    }
    SDL_RenderCopy(renderer, texture, nullptr, &buttonRect);
}

bool Button::intersects(const int otherX, const int otherY) const {
    if (otherX < x)
        return false;
    if (otherX > x + width)
        return false;
    if (otherY < y)
        return false;
    if (otherY > y + height)
        return false;
    return true;
}