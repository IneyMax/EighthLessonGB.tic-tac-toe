#pragma once

#pragma pack(push, 1)
class game_manager
{
private:
    int grid_line_;
    int win_line_;
    char player_sign_;
    char opponent_sign_;
    bool first_player_;
 
    int choose_grid_size ();
    int choose_win_line_lenght ();
    char choose_sign_player ();
    char choose_sign_opponent (char sign);
    bool choose_first_player ();
    void check_correct_input();

public:
    game_manager()
     : grid_line_(choose_grid_size ()),
       win_line_(choose_win_line_lenght ()),
       player_sign_(choose_sign_player ()),
       opponent_sign_(choose_sign_opponent (player_sign_)),
       first_player_(choose_first_player ())
    {
    }

    int get_grid_line() const;
    int get_grid_size ();
    int get_win_line() const;
    char get_player_sign() const;
    char get_opponent_sign() const;
    bool get_first_player() const;
    int get_player_choose();
};
#pragma pack(pop)
