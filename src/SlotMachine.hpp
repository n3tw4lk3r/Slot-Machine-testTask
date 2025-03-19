#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Button.hpp"
#include "Reel.hpp"
#include "SlotMachineState.hpp"
#include "SlotMachineStates.hpp"
#include "Text.hpp"

class SlotMachineState;

class SlotMachine {
private:
    int screenWidth;
    int screenHeight;
    int lastPrize;
    bool isRunning;
    std::vector<Reel> reels;
    std::vector<int> stopSymbols;
    Button startButton;
    Button stopButton;
    Text awardText;
    SlotMachineState* currentState;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    SlotMachine(int width, int height);
    inline SlotMachineState* getCurrentState() const;
    void toggle();
    void play();
    void setState(SlotMachineState& newState);
    ~SlotMachine();
    friend class IdleState;
    friend class SpinningState;
    friend class calculatePrizeState;
};
