#include <iostream>

#include "grid.h"
#include "game_manager.h"

/*
 * Небольшое пояснение к творящемуся тут хаосу:
 * Не знаю, помните ли вы, но в своё время вы мне скинули все лекции наперёд, за что я вам очень благодарен.
 * В основном, все ДЗ делались гораздо раньше, так что содержали кучу ошибок и отдельное спасибо на указание на них.
 * То же самое касается и этой мини-игры - сейчас всё сделал бы совсем по-другому, но переделовать всё нет времени - в настоящее время ищу работу джуном)
 * Эти крестики - нолики - попытка реализовать выбор клетки компьютером через веса + некая оценка потенциальной пользы клетки.
 * Соответственно, тут есть различные алгоритмы для динамического анализа клеток и перераспределения их весов
 * Скорее всего, эксперимент не удался. При том, что компьютер сопротивляется проигрышу, он не очень хочет выигрывать)
 * Вообще хотелось реализовать что-то вроде графов.
 * Тем не менее, при игре 3*3 это не заметно. Если интересно, что "под капотом" - раскоментируйте ниже main_grid.print_grid_weight()
 * Ещё интересна функция check_cell() - Она создана на основе быстрой сортировки, когда я пытался её реализовать.
 * В целом - для данного ИИ не хватает алгоритма, котрый бы говорил, что линия для победы не поместится, и нужно перестать туда делать ходы
 */


int main()
{
    game_manager main_game_manager; // Инициализация менеджера и всех начальных параметров
    grid main_grid (main_game_manager.get_win_line(), main_game_manager.get_grid_line()); // Инициализация стартовой сетки
    
    int turn {0};
    bool cur_player {main_game_manager.get_first_player()};
    while (turn < main_game_manager.get_grid_size())
    {
        main_grid.print_grid();
        // main_grid.print_grid_weight();
        
        switch (cur_player)
        {
        case true:
            {
                main_grid.add_sign(main_game_manager.get_player_choose(), main_game_manager.get_player_sign(), cur_player);
                cur_player = false;
                break;
            }
        case false:
            {
                main_grid.add_sign(main_grid.get_max_index(), main_game_manager.get_opponent_sign(), cur_player);
                cur_player = true;
                break;
            }
        }
        
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




