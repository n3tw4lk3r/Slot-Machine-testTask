#pragma once

#include "SlotMachineState.hpp"

class SlotMachineState;

class SlotMachine {
public:
    SlotMachine();
    inline SlotMachineState* getCurrentState() const;
    void toggle();
    void setState(SlotMachineState& newState);

private:
    SlotMachineState* currentState;
};
