#include "Player.h"
#include <iostream>

char player::get_sign()
{
    return sign_;
}

int player::get_pos()
{
    int pos{};
    std::cin >> pos;
    return pos;
}

