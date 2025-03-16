#include "SlotMachine.hpp"

#include "SlotMachineStates.hpp"

SlotMachine::SlotMachine() : currentState(&IdleState::getInstance()) {}

inline SlotMachineState* SlotMachine::getCurrentState() const {
    return currentState;
}

void SlotMachine::toggle() {
    currentState->toggle(this);
}

void SlotMachine::setState(SlotMachineState& newState) {
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}