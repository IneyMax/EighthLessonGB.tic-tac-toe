#include "Opponent.h"
#include <random>

char opponent::get_sign()
{
    return  sign_;
}

int get_random_number(int max)
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(1,max); // distribute results between 1 and 6 inclusive.
    return dist(gen);
}

int opponent::choose_cell()
{
    return get_random_number(8);
}


