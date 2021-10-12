#include <iostream>
#include "Game_Manager.h"

int main()
{
    /* Для вывода размеров классов*/
    std::cout << "Game Manager: " << sizeof(Game_Manager) << "\n";
    std::cout << "Grid: "<< sizeof(grid) << "\n";
    std::cout << "Opponent: "<< sizeof(opponent) << "\n";
    std::cout << "Player: "<< sizeof(player) << "\n";
    
    
    Game_Manager main_gm;
    switch (main_gm.main_game())
    {
        case 0:
            std::cout << "DRAW!!!";
            break;
        case 1:
            std::cout << "YOU WIN!!!";
            break;
        case 2:
            std::cout << "YOU LOSE!!!";
            break;
        default:
            std::cout << "ERROR!!!!";
    }
    return 0;
}











