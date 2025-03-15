#include "Game.hpp"

int main() {
    const int screenWidth = 640;
    const int screenHeight = 480;
    const std::string spriteFile = "resources/sprite.png";
    const int frameCnt = 6;
    const int totalWidth = 840;
    const int totalHeight = 345;
    const int frameWidth = 140;
    const SpriteSheet spriteSheet = {spriteFile, frameCnt, totalWidth, totalHeight, frameWidth};

    Game game(screenWidth, screenHeight, spriteSheet);
}