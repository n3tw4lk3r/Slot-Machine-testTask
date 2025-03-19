#pragma once

class SlotMachine;

class SlotMachineState {
public:
    virtual void enter(SlotMachine* slotMachine) = 0;
    virtual void toggle(SlotMachine* slotMachine) = 0;
    virtual void doWork(SlotMachine* SlotMachine) = 0;
    virtual void exit(SlotMachine* slotMachine) = 0;
    virtual ~SlotMachineState() {}
};