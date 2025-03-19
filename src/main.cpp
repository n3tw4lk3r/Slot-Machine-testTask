#include "SlotMachine.hpp"

int main(int argc, char** argv) {
    const int width = 900;
    const int height = 600;
    SlotMachine slotMachine(width, height);
    slotMachine.play();
    return 0;
}
