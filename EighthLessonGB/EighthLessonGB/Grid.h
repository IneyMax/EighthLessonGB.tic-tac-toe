#pragma once
#include <array>

struct cell
{
    int index;
    char sign;
    int weight;
};

#pragma pack(push, 1)
class grid
{
private:
    const int win_line_;
    const int grid_line_;
    int player_ {0};
    int grid_size_;
    cell max_cell_;
    cell *grid_array_;
    bool check_win_ {false};
    
    void grid_init(cell *empty_array, int size);
    int calc_start_weight (int index) const;
    void change_weight (int cur_pos, cell cur_cell);
    void add_weight (int cur_pos, int weight, int index);
    void victory_condition (int index);

    // Для динамического изменения весов:
    void check_up(int cur_pos, cell cur_cell, int index = 0);
    void check_down(int cur_pos, cell cur_cell, int index = 0);
    void check_left(int cur_pos, cell cur_cell, int index = 0);
    void check_right(int cur_pos, cell cur_cell, int index = 0);
    void check_up_left(int cur_pos, cell cur_cell, int index = 0);
    void check_down_left(int cur_pos, cell cur_cell, int index = 0);
    void check_up_right(int cur_pos, cell cur_cell, int index = 0);
    void check_down_right(int cur_pos, cell cur_cell, int index = 0);
    

public:
    grid(const int grid_line, const int win_line)
        :
        win_line_(win_line),
        grid_line_(grid_line),
        grid_size_(grid_line_ * grid_line_),
        grid_array_(new cell[grid_size_])
    {
        grid_init(grid_array_, grid_size_);
    }
    
    void print_grid() const;
    void print_grid_weight() const;
    void set_cur_player(int cur_turn);
    bool add_sign(int pos, char sign);
    int get_max_cell_index ();
    
};
#pragma pack(pop)


