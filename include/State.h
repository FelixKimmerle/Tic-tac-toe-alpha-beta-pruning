#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Move.h"

enum class Player
{
    None,
    Cross,
    Nought,
};

class State
{
private:
    Player field[3][3];
    Player turn;
    Player winner;
    int moves;

    void execute(Move move);
    void update_winner(Move move);
    int minimax(int alpha, int beta);

    void print_empty_line();
    void print_line(int row);

public:
    State();

    bool has_ended();
    Player get_winner();
    void read_move();
    void generate_move();

    void print();
};
#endif // GAME_H
