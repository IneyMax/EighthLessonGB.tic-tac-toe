#include "grid.h"

#include <array>
#include <iostream>

// Инициализация сетки значениями по умолчанию
void grid::grid_init(cell* empty_array, const int size)
{
    int index {0};
    while (index < size)
    {
        empty_array[index] = {index, (calculate_potencial_cell(index, grid_array_[index]) - 4), '+'}; // Заполняем индексами
        index ++;
    }
}

// Расчёт весов для ячейки - Устаревшая функция, не используется
int grid::calc_start_weight(const int index)
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
        if (grid_array_[index].index < 100 || grid_array_[index].weight < 1) // Добавление пробела для выравнивания сетки
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
        if (grid_array_[index].index < 10 || grid_array_[index].weight < 1) // Добавление пробела для выравнивания сетки
            {
            std::cout << " ";
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
void grid::add_sign(const int cell_index, const char sign, bool player)
{
    grid_array_[cell_index].sign = sign;
    if (player)
    {
        grid_array_[cell_index].weight += grid_line_; // для повышения веса у смежных ячеек
    }
    check_neighbours(grid_array_[cell_index]);
    grid_array_[cell_index].weight = 0;
}

// Получаем индекс клетки с наибольшим весом
int grid::get_max_index()
{
    int cell_index {0};
    int max_weight {0};
    int max_weight_index {0};
    while (cell_index < grid_size_) // для каждой ячейки
    {
        int new_potencial_cell {grid_array_[cell_index].weight + (calculate_potencial_cell(cell_index, grid_array_[cell_index]) % grid_line_)};
        if (max_weight < new_potencial_cell)
        {
            max_weight = new_potencial_cell;
            max_weight_index = cell_index;
        }
        cell_index++;
    }
    std::cout << "Opponent choose " << max_weight_index << "\n";
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
            if (v_element == h_element) // Пропускаем 0,0 для предотвращения рекурсии
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
        // Все ограничения при расстановке весов. TODO: преобразовать и сократить условие
        if (((move_hor > 0) && (temple_position % grid_line_ != 0)) || ((move_hor < 0) && (temple_position % grid_line_ != grid_line_ - 1)) || (!move_hor))
        {
            if (grid_array_[temple_position].sign == cur_cell.sign) // Если знак совпал
            {
                layer_index ++;
                check_win_condition(layer_index);
                if (layer_index == 1)
                {
                    check_cell( cur_cell_index, cur_cell, (-move_hor), (-move_vert), layer_index);
                }
                check_cell( temple_position, cur_cell, move_hor, move_vert, layer_index);
            }
            else if (grid_array_[temple_position].weight) // Если ячейка свободна
            {
                add_weight(temple_position, cur_cell, layer_index);
            }
        }
    }
}

// Расчёт потенциала клетки
int grid::calculate_potencial_cell(int cur_cell_index, cell cur_cell)
{
    int hor_line = 1 + potencial_line(cur_cell_index, cur_cell, 1, 0) + potencial_line(cur_cell_index, cur_cell, -1, 0);
    if (hor_line < win_line_)
    {
        hor_line = 0;
    }
    //std::cout << "Cell: " << cur_cell_index << " horiz line: " << hor_line << std::endl;
    int vert_line = 1 + potencial_line(cur_cell_index, cur_cell, 0, grid_line_) + potencial_line(cur_cell_index, cur_cell, 0, -grid_line_);
    if (vert_line < win_line_)
    {
        vert_line = 0;
    }
    //std::cout << "Cell: " << cur_cell_index << " vert_line: " << vert_line << std::endl;
    int diag_line_1 = 1 + potencial_line(cur_cell_index, cur_cell, 1, grid_line_) + potencial_line(cur_cell_index, cur_cell, -1, -grid_line_);
    if (diag_line_1 < win_line_)
    {
        diag_line_1 = 0;
    }
    //std::cout << "Cell: " << cur_cell_index << " diag_line_1: " << diag_line_1 << std::endl;
    int diag_line_2 = 1 + potencial_line(cur_cell_index, cur_cell,  1, -grid_line_) + potencial_line(cur_cell_index, cur_cell, -1, grid_line_);
    if (diag_line_2 < win_line_)
    {
        diag_line_2 = 0;
    }
    //std::cout << "Cell: " << cur_cell_index << " diag_line_2: " << diag_line_2 << std::endl;
    return hor_line + vert_line + diag_line_1 + diag_line_2;
}

// Возможные линии.
int grid::potencial_line(const int cur_cell_index, const cell cur_cell, const int move_hor, const int move_vert)
{
    const int temple_position = cur_cell_index + move_hor + move_vert; // ячейка на шаг впереди
    if (0 <= temple_position && temple_position < grid_size_) // в рамках поля
        if (((move_hor > 0) && (temple_position % grid_line_ != 0)) || ((move_hor < 0) && (temple_position % grid_line_ != grid_line_ - 1)) || (!move_hor)) // логика поля
        {
            if (grid_array_[temple_position].sign == cur_cell.sign || grid_array_[temple_position].weight) // если знак совпадает и ячейка свободна
            {
                return 1 + potencial_line (temple_position, cur_cell, move_hor, move_vert);
            }
        }
    return 0;
}

// Добавление веса в ячейку
void grid::add_weight(const int temple_position, const cell cur_cell, const int layer_index)
{
    int temple_extra_weight = calculate_potencial_cell(temple_position, cur_cell);
    if (layer_index > 0) // если не смежная ячейка - вес сильно повышается
    {
        if (temple_extra_weight) // При условии что у клетки есть потенциал
        {
            grid_array_[temple_position].weight += cur_cell.weight;
        }
        else
        {
            grid_array_[temple_position].weight = 1;
        }
    }
    else
        grid_array_[temple_position].weight += (temple_extra_weight + cur_cell.weight) % win_line_;
}

// Проверка победного условия
void grid::check_win_condition(const int layer)
{
    if (layer >= win_line_ - 1)
    {
        win_condition_ = true;
    }
}



