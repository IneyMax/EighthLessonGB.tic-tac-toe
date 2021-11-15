#pragma once

#pragma pack(push, 1)
struct cell
{
    int index;
    int weight;
    char sign;
};
#pragma pack(pop)


#pragma pack(push, 1)
class grid
{
private:
    const int win_line_;
    const int grid_line_;
    const int grid_size_;
    int empty_cell_;
    bool win_condition_ {false};
    cell *grid_array_;

public:
    grid(const int win_line, const int grid_line)
        : win_line_(win_line),
        grid_line_(grid_line),
        grid_size_(grid_line_ * grid_line_),
        empty_cell_(grid_size_),
        grid_array_(new cell[grid_size_])
    {
        grid_init(grid_array_, grid_size_);
    }

private:
    void grid_init(cell *empty_array, int size);
    int calc_start_weight (int index);
    void check_neighbours (cell cur_cell);
    void check_cell(int cur_cell_index, cell cur_cell, int move_hor = 0, int move_vert = 0, int layer_index = 0);
    int calculate_potencial_cell (int cur_cell_index, cell cur_cell);
    int potencial_line (int cur_cell_index, cell cur_cell, int move_hor, int move_vert);
    void add_weight (int cur_pos, int weight, int layer_index);
    void check_win_condition (int layer);

public:
    void print_grid() const;
    void print_grid_weight() const;
    void add_sign(int cell_index, char sign);
    int get_max_index () const;
    bool get_win_condition() const;

    ~grid()
    {
        delete[] grid_array_;
    }
};
#pragma pack(pop)
