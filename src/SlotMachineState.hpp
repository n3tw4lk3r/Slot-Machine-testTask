#pragma once

#include "SlotMachine.hpp"

class SlotMachine;

class SlotMachineState {
public:
    virtual void enter(SlotMachine* slotMachine) = 0;
    virtual void toggle(SlotMachine* slotMachine) = 0;
    virtual void exit(SlotMachine* slotMachine) = 0;
    virtual ~SlotMachineState() {}
};