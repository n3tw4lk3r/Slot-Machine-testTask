#pragma once

#include "SlotMachineState.hpp"
#include "SlotMachine.hpp"

class IdleState : public SlotMachineState {
public:
    ~IdleState() {}
    IdleState(const IdleState& other) = delete;
    IdleState operator=(const IdleState& other) = delete;

    void enter(SlotMachine* slotMachine) override {}
    void toggle(SlotMachine* slotMachine) override;
    void exit(SlotMachine* slotMachine) override {}
    static SlotMachineState& getInstance();

private:
    IdleState() {}
};

class SpinningState : public SlotMachineState {
public:
    ~SpinningState() {}
    SpinningState(const SpinningState& other) = delete;
    SpinningState operator =(const SpinningState& other) = delete;

    void enter(SlotMachine* slotMachine) override {}
    void toggle(SlotMachine* slotMachine) override;
    void exit(SlotMachine* slotMachine) override {}
    static SlotMachineState& getInstance();

private:
    SpinningState() {}
};

class DisplayPrizeState : public SlotMachineState {
public:
    ~DisplayPrizeState() {}
    DisplayPrizeState(const DisplayPrizeState& other) = delete;
    DisplayPrizeState operator=(const DisplayPrizeState& other) = delete;

    void enter(SlotMachine* slotMachine) override {}
    void toggle(SlotMachine* slotMachine) override;
    void exit(SlotMachine* slotMachine) override {}
    static SlotMachineState& getInstance();

private:
    DisplayPrizeState() {}
};