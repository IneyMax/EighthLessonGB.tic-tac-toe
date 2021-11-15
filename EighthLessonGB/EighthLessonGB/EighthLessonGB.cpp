#include <iostream>

#include "grid.h"
#include "game_manager.h"


int main()
{
    /* Для вывода размеров классов
    std::cout << "Game Manager: " << sizeof(game_manager) << "\n";
    std::cout << "Grid: "<< sizeof(grid) << "\n"; */
    
    game_manager main_game_manager; // Инициализация менеджера и всех начальных параметров
    grid main_grid (main_game_manager.get_win_line(), main_game_manager.get_grid_line()); // Инициализация стартовой сетки

    main_grid.print_grid();
    main_grid.print_grid_weight();
    int turn {0};
    bool cur_player {main_game_manager.get_first_player()};
    while (turn < main_game_manager.get_grid_size())
    {
        switch (cur_player)
        {
        case true:
            {//TODO Повысить вес ходов игрока и подобрать значения весов для полей
                main_grid.add_sign(main_game_manager.get_player_choose(), main_game_manager.get_player_sign());
                cur_player = false;
                break;
            }
        case false:
            {
                main_grid.add_sign(main_grid.get_max_index(), main_game_manager.get_opponent_sign());
                cur_player = true;
                break;
            }
        }
        
        main_grid.print_grid();
        main_grid.print_grid_weight(); //Для отслеживания весов
        turn ++;
        
        if (main_grid.get_win_condition())
        {
            if (!cur_player)
            {
                std::cout << "Player Win !!!";
            }
            else
                std::cout << "Opponent Win !!!";
            return 0;
        }
    }

    std::cout << "DRAW!!!";
    return 0;
}




