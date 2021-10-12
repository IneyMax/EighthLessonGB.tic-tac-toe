#include "Grid.h"
#include <iostream>

// Инициализация сетки
void grid::grid_init(cell *empty_array, const int size)
{
    int index {0};
    while (index < size)
    {
        empty_array[index].index = index + 1;
        empty_array[index].sign = '+';
        index ++;
    }
    // Расстановка весов для графов
    index = 0;
    while (index < size)
    {
        empty_array[index].weight = calc_start_weight(index);
        index ++;
    }
    // Помещаем координаты и вес в максимальную клетку из центра
    max_cell_.weight = grid_array_[(grid_size_ / 2)].weight;
    max_cell_.index = grid_array_[(grid_size_ / 2)].index;
}

// Рассчёт весов для старта
int grid::calc_start_weight (const int index) const
{
    int temple_weight {0};

    // Вертикаль 
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

    // Горизонталь
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
    
    // Для поля 3*3 вес диагоналей увеличен:
    if (grid_line_ == 3)
    {
        if (index % grid_line_  == index / grid_line_)
        {
            temple_weight += 4;
        }
        if (index % grid_line_  == (grid_size_- index - 1 ) / grid_line_)
        {
            temple_weight += 4;
        }
    }
    /*
    // Центр
    if (index == (grid_size_ / 2))
    {
        temple_weight += 5;
    }
    */
    return temple_weight;
}

//Отрисовка игрового поля
void grid::print_grid() const
{
    int index {0};
    while (index < grid_size_)
    {
        std::cout << "|";
        if (grid_array_[index].index < 10) // Добавление пробела для выравнивания сетки
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

// Временно для визуализации графов
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

// Добавление символа
bool grid::add_sign(const int pos, const char sign)
{
    max_cell_.weight = 0;
    const int index {(pos - 1)};
    grid_array_[index].sign = sign;
    change_weight(index, grid_array_[index]);
    grid_array_[index].weight = 0;
    grid_array_[index].index = 0;
    if (check_win_)
    {
        return true;
    }
    return false;
}

// Смена весов всех смежных ячеек
void grid::change_weight(const int cur_pos, const cell cur_cell)
{
    check_up(cur_pos, cur_cell);
    check_down(cur_pos, cur_cell);
    check_left(cur_pos, cur_cell);
    check_right(cur_pos, cur_cell);
    check_up_left(cur_pos, cur_cell);
    check_down_left(cur_pos, cur_cell);
    check_up_right(cur_pos, cur_cell);
    check_down_right(cur_pos, cur_cell);
}

// Добавляем вес по индексу ячейки
void grid::add_weight(const int cur_pos, const int weight, const int index)
{
    if (grid_array_[cur_pos].weight)
    {
        if (index != win_line_ - 1)
        {
            if (index > 0)
            {
                grid_array_[cur_pos].weight += weight;
            }
            else
            {
                grid_array_[cur_pos].weight += 1;
                
                if (player_) // Для добавления веса ходам игрока
                {
                    grid_array_[cur_pos].weight += 1;
                }
            }
        }
    }
    
}

// Проверка вверх
void grid::check_up(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos - grid_line_;
    if (temple_pos >= 0)
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_down(cur_pos, cur_cell, index);
            }
            check_up(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

// Проверка низ
void grid::check_down(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos + grid_line_;
    if (temple_pos <= grid_size_)
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_up(cur_pos, cur_cell, index);
            }
            check_down(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

// Прооверка влево
void grid::check_left(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos - 1;
    if (temple_pos % grid_line_ != grid_line_ - 1)
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_right(cur_pos, cur_cell, index);
            }
            check_left(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

//Проверка вправо
void grid::check_right(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos + 1;
    if (temple_pos % grid_line_ != 0)
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_left(cur_pos, cur_cell, index);
            }
            check_right(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

// Вверх лево
void grid::check_up_left(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos - grid_line_ - 1;
    if ((temple_pos % grid_line_ != grid_line_ - 1) && (temple_pos >= 0))
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_down_right(cur_pos, cur_cell, index);
            }
            check_up_left(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

// Вверх вправо
void grid::check_up_right(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos - grid_line_ + 1;
    if ((temple_pos >= 0) && (temple_pos % grid_line_ != 0))
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_down_left(cur_pos, cur_cell, index);
            }
            check_up_right(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

// Вниз влево
void grid::check_down_left(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos + grid_line_ - 1;
    if ((temple_pos % grid_line_ != grid_line_ - 1) && (temple_pos >= 0))
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_up_right(cur_pos, cur_cell, index);
            }
            check_down_left(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

// Вниз вправо
void grid::check_down_right(const int cur_pos, const cell cur_cell, int index)
{
    victory_condition(index);
    const int temple_pos = cur_pos + grid_line_ + 1;
    if ((temple_pos % grid_line_ != 0) && (temple_pos < grid_size_))
    {
        if (grid_array_[temple_pos].sign == cur_cell.sign)
        {
            index ++;
            if (index == 1)
            {
                check_up_left(cur_pos, cur_cell, index);
            }
            check_down_right(temple_pos, cur_cell, index);
        }
        else add_weight(temple_pos, cur_cell.weight, index);
    }
}

// Поиск клетки с макисмальным весом
int grid::get_max_cell_index()
{
    int cell_index {0};
    while (cell_index < grid_size_)
    {
        if (grid_array_[cell_index].weight > max_cell_.weight)
        {
            max_cell_ = grid_array_[cell_index];
        }
        cell_index ++;
    }
    return max_cell_.index;
}

// Для распознавания чей ход
void grid::set_cur_player(int cur_player)
{
    player_ = cur_player;
}

void grid::victory_condition(int index)
{
    if (index >= win_line_ - 1)
    {
        check_win_ = true;
    }
}



