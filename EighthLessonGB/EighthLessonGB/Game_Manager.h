#pragma once
#include "Grid.h"
#include "Opponent.h"
#include "Player.h"


enum e_turn
{
    opponent_turn,
    player_turn
};

#pragma pack(push, 1)
class Game_Manager
{
private:
    int grid_line_;
    int round_counter_{};
    grid main_grid_;
    player main_player_;
    opponent main_opponent_;
    e_turn cur_turn_;

    int choose_win_line_lenght ();
    int choose_grid_size ();
    e_turn choose_first_player ();
    char choose_signs ();
    char choose_signs_op (char sign);
    void check_correct_input();

public:
    Game_Manager()
        :
        grid_line_(choose_grid_size()),
        main_grid_(grid_line_, choose_win_line_lenght()),
        main_player_(choose_signs()),
        main_opponent_(choose_signs_op(main_player_.get_sign())),
        cur_turn_(choose_first_player())
    {
    }

    int main_game();
};
#pragma pack(pop)