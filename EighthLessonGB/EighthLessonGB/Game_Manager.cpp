#include "Game_Manager.h"

// Выбор длины линии для победы
int Game_Manager::choose_win_line_lenght()
{
    int win_line {3};
    return win_line;
}

// Определение первого игрока
TURN Game_Manager::choose_first_player()
{
    /*
    std::cout << "Will you be the first player? (Yes/No)\n";
    std::string first_player;
    std::cin >> first_player;
    if (first_player == "Yes\n")
    {
        std::cout << "Ok\n";*/
        return OPPONENT_TURN;/*
    }
    else
        return false;*/
}

// Выбор знаков для игрока
char Game_Manager::choose_signs()
{/*
    std::cout << "Are you going to play with crosses or toe? (Cross / Toe) \n";
    std::string signs;
    std::cin >> signs;
    if (signs == "Cross")
    {
        std::cout << "Ok, you sign '*'\n";*/
        return '*';/*
    }
    else
    {
        std::cout << "Ok, you sign '0'\n";
        return '0';
    }*/
}

// Выбор знаков для оппонента
char Game_Manager::choose_signs_op(char sign)
{/*
    if (sign == '*')
    {
        std::cout << "You opponent sign: '0'\n";*/
        return '-';/*
    }
    else
        std::cout << "You opponent sign: '*'\n";
        return '*';*/
}

// Запрос размера игрового поля - на будущее
int Game_Manager::choose_grid_size()
{
    int line_lenght {3}; // При выборе размера линии для победы - добавить ограничение в зависимости от размера поля
    // Добавить, чтобы поле обязательно было нечетное
    return (line_lenght);
}

//Основной игровой цикл
int Game_Manager::main_game()
{
    main_grid_.print_grid();
    main_grid_.print_grid_weight();
    
    TURN cur_turn {OPPONENT_TURN};
    do
    {
        switch (cur_turn)
        {
        case OPPONENT_TURN:
            main_grid_.set_cur_turn(OPPONENT_TURN);
            if (main_grid_.add_sign(main_grid_.get_max_cell_index(), main_opponent_.get_sign()))
            {
                return 2;
            }
            cur_turn = PLAYER_TURN;
            break;
            
        case PLAYER_TURN:
            main_grid_.set_cur_turn(PLAYER_TURN);
            if (main_grid_.add_sign(main_player_.get_pos(), main_player_.get_sign()))
            {
                return 1;
            }
            cur_turn = OPPONENT_TURN;
            break;
            
        default:
            return 4;
        }
        
        main_grid_.print_grid();
        main_grid_.print_grid_weight();
    }
    while (true);
}




