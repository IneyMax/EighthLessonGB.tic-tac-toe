#include "grid.h"

#include <array>
#include <iostream>

// Инициализация сетки значениями по умолчанию
void grid::grid_init(cell* empty_array, const int size)
{
    int index {0};
    while (index < size)
    {
        empty_array[index] = {index, '+', calc_start_weight(index)}; // Заполняем индексами
        index ++;
    }
}

// Расчёт весов для ячейки
int grid::calc_start_weight(const int index) const
{
    int temple_weight {0};

    // Вертикали
    if ((index % grid_line_ >= 0) && (index % grid_line_ < grid_line_))
    {
        if (index / grid_line_ <= grid_line_ / 2)
        {
            temple_weight += index / grid_line_ + 1;
        }
        if (index / grid_line_ > grid_line_ / 2)
        {
            temple_weight += (grid_line_ - index / grid_line_);
        }
    }

    // Горизонтали
    if ((index >= 0) && (index < grid_size_))
    {
        
        if (index % grid_line_ <= grid_line_ / 2)
        {
            temple_weight += (index % grid_line_) + 1;
        }
        if (index % grid_line_ > grid_line_ / 2)
        {
            temple_weight += (grid_line_ - index % grid_line_) ;
        }
    }

    // Диагонали
    if (index % grid_line_  == index / grid_line_)
    {
        temple_weight += 4;
    }
    if (index % grid_line_  == (grid_size_- index - 1 ) / grid_line_)
    {
        temple_weight += 4;
    }
    
    return temple_weight;
}

// Отрисовка сетки
void grid::print_grid() const
{
    int index {0};
    while (index < grid_size_)
    {
        std::cout << "|";
        if (grid_array_[index].index < 10 || grid_array_[index].weight < 1) // Добавление пробела для выравнивания сетки
            {
            std::cout << " ";
            }

        if (grid_array_[index].weight)
        {
            std::cout << grid_array_[index].index;
        }
        else
        {
            std::cout << grid_array_[index].sign;
        }
        index ++;
        
        if (index % grid_line_ == 0) // Перенос строки в конце линии
            {
            std::cout << "|\n";
            }
    }
    std::cout << "\n";
}

// Отрисовка весов сетки
void grid::print_grid_weight() const
{
    int index {0};
    while (index < grid_size_)
    {
        std::cout << "|";
        if (grid_array_[index].weight < 10) // Добавление пробела для выравнивания сетки
            {
            std::cout << " ";
            }
        
        std::cout << grid_array_[index].weight;
        
        index ++;
        
        if (index % grid_line_ == 0) // Перенос строки в конце линии
            {
            std::cout << "|\n";
            }
    }
    std::cout << "\n";
}

// Добавления символа в сетку
void grid::add_sign(const int cell_index, const char sign)
{
    grid_array_[cell_index].sign = sign;
    check_neighbours(grid_array_[cell_index]);
    grid_array_[cell_index].weight = 0;
}

// Получаем индекс клетки с наибольшим весом
int grid::get_max_index() const
{
    int cell_index {0};
    int max_weight {0};
    int max_weight_index {0};
    while (cell_index < grid_size_)
    {
        if (max_weight < grid_array_[cell_index].weight)
        {
            max_weight = grid_array_[cell_index].weight;
            max_weight_index = cell_index;
        }
        cell_index++;
    }
    return max_weight_index;
}

//Получаем состояние победного условия
bool grid::get_win_condition() const
{
    return win_condition_;
}

// Проверка всех соседей
void grid::check_neighbours(const cell cur_cell)
{
    std::array<int, 3> vert_array {-grid_line_, grid_line_};
    std::array<int, 3> hor_array {-1, 1};
    for (const auto v_element : vert_array) // Для прохода по всем соседям
    {
        for (const auto h_element : hor_array)
        {
            if (v_element == 0 && h_element == 0) // Пропускаем 0,0 для предотвращения рекурсии
            {
                continue;
            }
            check_cell(cur_cell.index, cur_cell, h_element,v_element);
        }
    }
}

// Алгоритм движения по сетке (Рекурсивный)
void grid::check_cell(const int cur_cell_index, const cell cur_cell, const int move_hor, const int move_vert, int layer_index)
{
    const int temple_position = cur_cell_index + move_hor + move_vert;
    if (0 <= temple_position && temple_position < grid_size_) // Чтобы всё происходило в рамках поля
    {
        if (grid_array_[temple_position].sign == cur_cell.sign)
            {
            layer_index ++;
            check_win_condition(layer_index);
            if (layer_index == 1)
            {
                check_cell( cur_cell_index, cur_cell, (-move_hor), (-move_vert), layer_index);
            }
            check_cell( temple_position, cur_cell, move_hor, move_vert, layer_index);
            }
        else
            add_weight(temple_position, cur_cell.weight, layer_index);
    }
}

// Добавление веса в ячейку
void grid::add_weight(const int cur_pos, const int weight, const int layer_index)
{
    if (grid_array_[cur_pos].weight)
    {
        if (layer_index > 0)
        {
            grid_array_[cur_pos].weight += weight;
        }
        else
            grid_array_[cur_pos].weight += 1;
    }
}


void grid::check_win_condition(const int layer)
{
    if (layer >= win_line_ - 1)
    {
        win_condition_ = true;
    }
}

