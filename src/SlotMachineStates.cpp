#include "SlotMachineStates.hpp"
#include "SlotMachine.hpp"

void IdleState::toggle(SlotMachine* slotMachine) {
    slotMachine->setState(SpinningState::getInstance());
}

SlotMachineState& IdleState::getInstance() {
    static IdleState singleton;
    return singleton;
}

void SpinningState::toggle(SlotMachine* slotMachine) {
    slotMachine->setState(DisplayPrizeState::getInstance());
}

SlotMachineState& SpinningState::getInstance() {
    static SpinningState singleton;
    return singleton;
}

void DisplayPrizeState::toggle(SlotMachine* slotMachine) {
    slotMachine->setState(IdleState::getInstance());
}

SlotMachineState& DisplayPrizeState::getInstance() {
    static DisplayPrizeState singleton;
    return singleton;
}