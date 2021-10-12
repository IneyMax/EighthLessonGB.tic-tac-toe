#include "Game_Manager.h"

#include <iostream>

// Выбор длины линии для победы
int Game_Manager::choose_win_line_lenght()
{
    if (grid_line_ == 3)
    {
        return 3;
    }
    while (true)
    {
        std::cout << "Enter the line length to win: \n";
        int win_line {};
        std::cin >> win_line;
        if (win_line > 2 && win_line <= grid_line_)
        {
            return win_line;
        }
        check_correct_input();
    }
}

// Определение первого игрока
e_turn Game_Manager::choose_first_player()
{
    while (true)
    {
        std::cout << "Will you be the first player? (Yes/No)\n";
        std::string first_player;
        std::cin >> first_player;
        if ((first_player == "Yes") || (first_player == "yes"))
        {
            return player_turn;
        }
        if ((first_player == "No") || (first_player == "no"))
        {
            return opponent_turn;
        }
        check_correct_input();
    }
}

// Выбор знаков для игрока
char Game_Manager::choose_signs()
{
    while (true)
    {
        std::cout << "Are you going to play with crosses or toe? (Cross / Toe) \n";
        std::string signs;
        std::cin >> signs;
        if (signs == "Cross" || signs == "cross" || signs == "*")
        {
            std::cout << "Ok, you sign '*'\n";
            return '*';
        }
        if (signs == "Toe" || signs == "toe"  || signs == "o")
        {
            std::cout << "Ok, you sign 'o'\n";
            return 'o';
        }
        check_correct_input();
    }
}

// Выбор знаков для оппонента
char Game_Manager::choose_signs_op(const char sign)
{
    if (sign == '*')
    {
        std::cout << "You opponent sign: 'o'\n";
        return 'o';
    }
    else
        std::cout << "You opponent sign: '*'\n";
        return '*';
}

// Запрос размера игрового поля
int Game_Manager::choose_grid_size()
{
    while (true)
    {
        std::cout << "Enter the size of the field (must be odd): \n";
        int line_lenght {};
        std::cin >> line_lenght;
        if ((line_lenght > 2) && (line_lenght % 2 == 1) && (line_lenght < 30))
        {
            return (line_lenght);
        }
        check_correct_input();
    }
}

//Основной игровой цикл
int Game_Manager::main_game()
{
    main_grid_.print_grid();
    //main_grid_.print_grid_weight();
    
    do
    {
        round_counter_ ++;
        switch (cur_turn_)
        {
        case opponent_turn:
            main_grid_.set_cur_player(opponent_turn);
            if (main_grid_.add_sign(main_grid_.get_max_cell_index(), main_opponent_.get_sign()))
            {
                main_grid_.print_grid();
                //main_grid_.print_grid_weight();
                return 2;
            }
            cur_turn_ = player_turn;
            break;
            
        case player_turn:
            main_grid_.set_cur_player(player_turn);
            if (main_grid_.add_sign(main_player_.get_pos(), main_player_.get_sign()))
            {
                main_grid_.print_grid();
                //main_grid_.print_grid_weight();
                return 1;
            }
            cur_turn_ = opponent_turn;
            break;
            
        default:
            return 3;
        }
        
        main_grid_.print_grid();
        //main_grid_.print_grid_weight();
    }
    while (round_counter_ <= ((grid_line_ * grid_line_) - 1));

    return 0;
}

// Для корретного считывания ввода
void Game_Manager::check_correct_input()
{
    if (std::cin.fail()) // если предыдущее извлечение не выполнилось или произошло переполнение,
        {
        std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
        std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
        }
}


