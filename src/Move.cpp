#include "Move.h"

#include <iostream>

Move::Move(int column, int row)
{
    this->column = column;
    this->row = row;
}

int Move::get_column()
{
    return column;
}
int Move::get_row()
{
    return row;
}

void Move::print()
{
    std::cout << static_cast<char>('a' + column) << row + 1;
}
