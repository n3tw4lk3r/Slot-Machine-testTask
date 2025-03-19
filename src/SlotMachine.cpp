#include "SlotMachine.hpp"

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Button.hpp"
#include "Reel.hpp"
#include "SlotMachineState.hpp"
#include "SlotMachineStates.hpp"
#include "Text.hpp"

SlotMachine::SlotMachine(const int width, const int height) :
    screenWidth(width),
    screenHeight(height),
    lastPrize(0),
    isRunning(true),
    startButton(700, 250, 100, 50),
    stopButton(700, 350, 100, 50),
    awardText(110, 50, 300, 100),
    currentState(&IdleState::getInstance())
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    window = SDL_CreateWindow("Тестовое задание", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screenWidth,
                              screenHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    reels = { Reel(100, 200, renderer), Reel(210, 200, renderer),
              Reel(320, 200, renderer) };
    stopSymbols = std::vector<int>(reels.size(), -1);
}

inline SlotMachineState* SlotMachine::getCurrentState() const {
    return currentState;
}

void SlotMachine::toggle() {
    currentState->toggle(this);
}

void SlotMachine::play() {
    currentState->doWork(this);
    if (isRunning)
        toggle();
}

void SlotMachine::setState(SlotMachineState& newState) {
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
    play();
}

SlotMachine::~SlotMachine() {
    Reel::destroyTextures();
    awardText.closeFont();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}
