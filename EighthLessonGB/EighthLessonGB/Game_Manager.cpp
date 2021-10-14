#include "game_manager.h"
#include <iostream>

// Выбор размера игрового поля
int game_manager::choose_grid_size()
{
    while (true)
    {
        std::cout << "Enter the size of the field (must be odd): \n";
        int line_lenght {};
        std::cin >> line_lenght;
        if ((line_lenght > 2) && (line_lenght % 2 == 1) && (line_lenght < 30))
        {
            return line_lenght;
        }
        check_correct_input();
    }
}

// Выбор длины линии для победы
int game_manager::choose_win_line_lenght()
{
    // при игре 3*3 можно играть только три в ряд
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

// Выбор знаков для игрока
char game_manager::choose_sign_player()
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
char game_manager::choose_sign_opponent(const char sign)
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

// Определение первого игрока
bool game_manager::choose_first_player()
{
    while (true)
    {
        std::cout << "Will you be the first player?\n";
        std::string first_player;
        std::cin >> first_player;
        if (first_player == "Yes" || first_player == "yes" || first_player == "1")
        {
            std::cout << "Okay, you'll be the first player\n";
            return true;
        }
        else if (first_player == "No" || first_player == "no" || first_player == "2")
        {
            std::cout << "Okay, you'll be the second player\n";
            return false;
        }
        check_correct_input();
    }
}

void game_manager::check_correct_input()
{
    if (std::cin.fail()) // если предыдущее извлечение не выполнилось или произошло переполнение,
        {
        std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
        std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
        }
}

int game_manager::get_grid_line() const
{
    return grid_line_;
}

int game_manager::get_grid_size()
{
    return grid_line_ * grid_line_;
}

int game_manager::get_win_line() const
{
    return win_line_;
}

char game_manager::get_player_sign() const
{
    return player_sign_;
}

char game_manager::get_opponent_sign() const
{
    return opponent_sign_;
}

bool game_manager::get_first_player() const
{
    return first_player_;
}

// Запрос ввода позиции у игрока
int game_manager::get_player_choose()
{
    while (true)
    {
        int pos;
        std::cin >> pos;
        if ((pos >= 0) && (pos <= grid_line_ * grid_line_))
        {
            std::cout << "Player choose " << pos << "\n";
            return pos;
        }
        check_correct_input();
    }
}


