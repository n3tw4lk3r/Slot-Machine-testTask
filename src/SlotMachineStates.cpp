#include "SlotMachineStates.hpp"

#include <algorithm>
#include <chrono>
#include <string>

#include <SDL2/SDL.h>

#include "SlotMachine.hpp"
#include "SlotMachineState.hpp"
#include "Utils.hpp"

void IdleState::toggle(SlotMachine* slotMachine) {
    slotMachine->setState(SpinningState::getInstance());
}

void IdleState::doWork(SlotMachine* slotMachine) {
    SDL_Event event;
    while (true) {
        bool exited = false;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                slotMachine->isRunning = false;
                exited = true;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int clickX = event.button.x;
                int clickY = event.button.y;
                if (slotMachine->startButton.intersects(clickX, clickY)) {
                    for (auto& reel : slotMachine->reels)
                        reel.isSpinning = true;
                    exited = true;
                    break; // ==> SpinningState
                }
            }
        }
        if (exited)
            break;
        SDL_SetRenderDrawColor(slotMachine->renderer, 0, 128, 0, 255);
        SDL_RenderClear(slotMachine->renderer);
        for (auto& reel : slotMachine->reels)
            reel.render();
        slotMachine->startButton.render(slotMachine->renderer,
                                        "assets/start.png");
        slotMachine->stopButton.render(slotMachine->renderer,
                                       "assets/stop.png");
        auto prizeText = std::to_string(slotMachine->lastPrize);
        std::string text = "Your prize: " + prizeText;
        slotMachine->awardText.render(slotMachine->renderer, text);
        SDL_RenderPresent(slotMachine->renderer);
        SDL_Delay(25);
    }
}

SlotMachineState& IdleState::getInstance() {
    static IdleState singleton;
    return singleton;
}

void SpinningState::toggle(SlotMachine* slotMachine) {
    slotMachine->setState(calculatePrizeState::getInstance());
}

void SpinningState::doWork(SlotMachine* slotMachine) {
    slotMachine->stopSymbols.assign(slotMachine->stopSymbols.size(), -1);
    std::vector<bool> reelsStopped(slotMachine->reels.size(), false);
    auto startSpinningTimepoint = std::chrono::steady_clock::now();
    SDL_Event event;
    while (true) {
        bool exited = false;
        auto currentTimepoint = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(
                    currentTimepoint - startSpinningTimepoint).count();
        if (diff >= 5)
            stopReels(slotMachine);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                slotMachine->isRunning = false;
                exited = true;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int clickX = event.button.x;
                int clickY = event.button.y;
                if (slotMachine->stopButton.intersects(clickX, clickY)) {
                    stopReels(slotMachine);
                    break; // ==> DisplayAwardState
                }
            }
        }
        if (exited)
            break;
        for (size_t i = 0; i < slotMachine->reels.size(); ++i) {
            slotMachine->reels[i].update();
            if (slotMachine->reels[i].getCurrentSymbolIdx() == 
                                        slotMachine->stopSymbols[i]) {
                slotMachine->reels[i].isSpinning = false;
                reelsStopped[i] = true;
            }
        }
        SDL_SetRenderDrawColor(slotMachine->renderer, 0, 128, 0, 255);
        SDL_RenderClear(slotMachine->renderer);
        for (auto& reel : slotMachine->reels)
            reel.render();
        slotMachine->startButton.render(slotMachine->renderer,
                                        "assets/start.png");
        slotMachine->stopButton.render(slotMachine->renderer,
                                       "assets/stop.png");
        SDL_RenderPresent(slotMachine->renderer);
        SDL_Delay(25);
        if (std::all_of(reelsStopped.begin(), reelsStopped.end(),
                        [](bool x) { return x; })) {
            break;
        }
    }
}

SlotMachineState& SpinningState::getInstance() {
    static SpinningState singleton;
    return singleton;
}

inline void SpinningState::stopReels(SlotMachine* slotMachine) {
    for (size_t i = 0; i < slotMachine->reels.size(); ++i) {
        int stopSymbol = utils::generateRandomNumber() %
                         slotMachine->reels[i].symbols.size();
        slotMachine->stopSymbols[i] =
                    slotMachine->reels[i].symbols[stopSymbol];
    }
}

void calculatePrizeState::toggle(SlotMachine* slotMachine) {
    slotMachine->setState(IdleState::getInstance());
}

void calculatePrizeState::doWork(SlotMachine* slotMachine) {
    auto onReel0 = slotMachine->reels[0].getCurrentSymbolIdx();
    auto onReel1 = slotMachine->reels[1].getCurrentSymbolIdx();
    auto onReel2 = slotMachine->reels[2].getCurrentSymbolIdx();
    int prize;
    if (onReel0 == onReel1 && onReel0 == onReel2 && onReel1 == onReel2)
        prize = 300;
    else if (onReel0 == onReel1 || onReel0 == onReel2 || onReel1 == onReel2)
        prize = 200;
    else
        prize = 100;
    slotMachine->lastPrize = prize;
}

SlotMachineState& calculatePrizeState::getInstance() {
    static calculatePrizeState singleton;
    return singleton;
}