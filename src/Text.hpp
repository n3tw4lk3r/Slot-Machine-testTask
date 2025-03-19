#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SlotMachine;

class Text {
public:
    explicit Text(const int x, const int y, const int w, const int h);
    void render(SDL_Renderer* renderer, const std::string text);
    ~Text();

private:
    const int x;
    const int y;
    const int width;
    const int height;
    bool textureLoaded;
    bool fontLoaded;
    std::string text;
    SDL_Texture* texture;
    TTF_Font* font;
    void closeFont();
    friend class SlotMachine;
};