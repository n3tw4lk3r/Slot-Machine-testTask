#include "Utils.hpp"

#include <algorithm>
#include <random>

int utils::generateRandomNumber() {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution;
    return distribution(device);
}

void utils::shuffleVector(std::vector<int>& vector) {
    auto rangomEngine = std::default_random_engine();
    std::shuffle(std::begin(vector), std::end(vector), rangomEngine);
}
