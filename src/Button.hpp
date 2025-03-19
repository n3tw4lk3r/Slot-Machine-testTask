#pragma once

#include <cassert>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Button {
public:
    explicit Button(const int x, const int y, const int w, const int h);
    void render(SDL_Renderer* renderer, std::string path);
    bool intersects(const int otherX, const int otherY) const;
    ~Button();
    
private:
    const int x;
    const int y;
    const int width;
    const int height;
    const std::string pathToImg;
    bool textureLoaded = false;
    SDL_Texture* texture;
};