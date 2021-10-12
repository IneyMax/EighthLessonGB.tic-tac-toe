#pragma once
#include "Grid.h"
#include "Opponent.h"
#include "Player.h"


enum TURN
{
    OPPONENT_TURN,
    PLAYER_TURN
};


#pragma pack(push, 1)
class Game_Manager
{
private:
    grid main_grid_;
    player main_player_;
    opponent main_opponent_;
    TURN cur_turn_;

    int choose_win_line_lenght ();
    int choose_grid_size ();
    TURN choose_first_player ();
    char choose_signs ();
    char choose_signs_op (char sign);

public:
    Game_Manager()
        : main_grid_(choose_grid_size(), choose_win_line_lenght()),
          main_player_(choose_signs()),
          main_opponent_(choose_signs_op(main_player_.get_sign())),
          cur_turn_(choose_first_player())
    {
    }
    int main_game();
};
#pragma pack(pop)