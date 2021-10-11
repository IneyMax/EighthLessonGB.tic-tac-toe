#include <iostream>

#include "Game_Manager.h"

int main()
{
    /* Для вывода размеров классов
    std::cout << "Game Manager: " << sizeof(Game_Manager) << "\n";
    std::cout << "Grid: "<< sizeof(grid) << "\n";
    std::cout << "Opponent: "<< sizeof(opponent) << "\n";
    std::cout << "Player: "<< sizeof(player) << "\n";
    */
    
    Game_Manager main_gm;
    if (main_gm.main_game())
    {
        std::cout << "You Win!";
    }
    else
        std::cout << "You Lose!";
    return 0;
}











