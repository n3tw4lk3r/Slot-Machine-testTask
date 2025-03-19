#pragma once

#include "SlotMachine.hpp"
#include "SlotMachineState.hpp"

class IdleState : public SlotMachineState {
public:
    ~IdleState() = default;
    IdleState(const IdleState& other) = delete;
    IdleState operator=(const IdleState& other) = delete;

    void enter(SlotMachine* slotMachine) override {}
    void toggle(SlotMachine* slotMachine) override;
    void doWork(SlotMachine* slotMachine) override;
    void exit(SlotMachine* slotMachine) override {}
    static SlotMachineState& getInstance();

private:
    IdleState() {}
};

class SpinningState : public SlotMachineState {
public:
    ~SpinningState() = default;
    SpinningState(const SpinningState& other) = delete;
    SpinningState operator =(const SpinningState& other) = delete;

    void enter(SlotMachine* slotMachine) override {}
    void toggle(SlotMachine* slotMachine) override;
    void doWork(SlotMachine* slotMachine) override;
    void exit(SlotMachine* slotMachine) override {}
    static SlotMachineState& getInstance();

private:
    SpinningState() {}
    inline void stopReels(SlotMachine* slotMachine);
};

class calculatePrizeState : public SlotMachineState {
public:
    ~calculatePrizeState() = default;
    calculatePrizeState(const calculatePrizeState& other) = delete;
    calculatePrizeState operator=(const calculatePrizeState& other) = delete;

    void enter(SlotMachine* slotMachine) override {}
    void toggle(SlotMachine* slotMachine) override;
    void doWork(SlotMachine* slotMachine) override;
    void exit(SlotMachine* slotMachine) override {}
    static SlotMachineState& getInstance();

private:
calculatePrizeState() {}
};