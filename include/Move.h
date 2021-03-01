#ifndef MOVE_H
#define MOVE_H

class Move
{
private:
    int column;
    int row;
public:
    Move(int column, int row);

    int get_column();
    int get_row();
    void print();
};

#endif // MOVE_H
