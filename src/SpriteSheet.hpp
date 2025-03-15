#pragma once

#include <string>

struct SpriteSheet {
    const std::string& pathTo;
    const int frameCnt;
    const int totalWidth;
    const int totalHeight;
    const int frameWidth;
};