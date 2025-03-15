#include "TextureWrapper.hpp"

#include <cassert>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

TextureWrapper::TextureWrapper() :
    texturePtr(nullptr),    
    width(0),
    height(0)
{}

TextureWrapper::~TextureWrapper()
{
    free();
}

bool TextureWrapper::loadImageFromFile(SDL_Renderer* rendererPtr, const std::string& path) {
    free();
    SDL_Surface* surfacePtr = IMG_Load(path.c_str());
    assert(surfacePtr != nullptr);
    auto mappedPixel = SDL_MapRGB(surfacePtr->format, 0, 255, 255);
    SDL_SetColorKey(surfacePtr, SDL_TRUE, mappedPixel);
    auto newTexturePtr = SDL_CreateTextureFromSurface(rendererPtr, surfacePtr);
    assert(newTexturePtr != nullptr);
    width = surfacePtr->w;
    height = surfacePtr->h;
    SDL_FreeSurface(surfacePtr);
    texturePtr = newTexturePtr;
    return texturePtr != nullptr;
}

void TextureWrapper::free() {
    if (texturePtr != nullptr) {
        SDL_DestroyTexture(texturePtr);
        texturePtr = nullptr;
        width = 0;
        height = 0;
    }
}

void TextureWrapper::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texturePtr, red, green, blue);
}

void TextureWrapper::setBlendMode(SDL_BlendMode blendMode) {
    SDL_SetTextureBlendMode(texturePtr, blendMode);
}

void TextureWrapper::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texturePtr, alpha);
}

void TextureWrapper::render(SDL_Renderer* rendererPtr, SDL_Rect* clip, const int x, const int y) {
    SDL_Rect renderRect = {x, y, width, height};
    if (clip != nullptr) {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }
    SDL_RenderCopy(rendererPtr, texturePtr, clip, &renderRect);
}

int TextureWrapper::getWidth() const {
    return width;
}

int TextureWrapper::getHeight() const {
    return height;
}
