#pragma once 

#include <cassert>
#include <string>

#include <SDL2/SDL.h>

class TextureWrapper {
public:
    TextureWrapper();
    ~TextureWrapper();
    bool loadImageFromFile(SDL_Renderer* rendererPtr, const std::string& path);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blendMode);
    void setAlpha(Uint8 alpha);
    void render(SDL_Renderer* rendererPtr, SDL_Rect* clip, const int x, const int y);
    int getWidth() const;
    int getHeight() const;

private:
    SDL_Texture* texturePtr;
    int width;
    int height; 
};