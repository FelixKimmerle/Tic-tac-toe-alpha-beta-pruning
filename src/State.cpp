#include "State.h"

#include <iostream>
#include <random>

const static int WIN = 1;
const static int LOSS = -1;
const static int DRAW = 0;

State::State()
{
    //set the random seed to the number of seconds since the first January 1970 00:00
    srand(time(0));
    //Clear the field
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            field[column][row] = Player::None;
        }
    }

    //Cross alsways has the first move.
    turn = Player::Cross;
    //we dont habe a winner yet.
    winner = Player::None;
    moves = 0;
}

void State::execute(Move move)
{
    field[move.get_column()][move.get_row()] = turn;

    //Switch the Player that is on the turn.
    if (turn == Player::Cross)
    {
        turn = Player::Nought;
    }
    else if (turn == Player::Nought)
    {
        turn = Player::Cross;
    }

    moves++;
    update_winner(move);
}

void State::update_winner(Move move)
{
    int changed_column = move.get_column();
    int changed_row = move.get_row();

    //Check the column
    if (field[changed_column][0] != Player::None &&
        field[changed_column][0] == field[changed_column][1] &&
        field[changed_column][1] == field[changed_column][2])
    {
        winner = field[changed_column][0];
    }

    //Check the row
    if (field[0][changed_row] != Player::None &&
        field[0][changed_row] == field[1][changed_row] &&
        field[1][changed_row] == field[2][changed_row])
    {
        winner = field[0][changed_row];
    }

    //Check if the changed cell is on the diagonal. See: https://en.wikipedia.org/wiki/Main_diagonal
    if (changed_column == changed_row)
    {
        //Check the diagonal
        if (field[0][0] != Player::None &&
            field[0][0] == field[1][1] &&
            field[1][1] == field[2][2])
        {
            winner = field[0][0];
        }
    }

    //Check if the changed cell is on the anti diagonal. See: https://en.wikipedia.org/wiki/Main_diagonal#Antidiagonal
    if (changed_column + changed_row == 2)
    {
        //Check the anti diagonal
        if (field[2][0] != Player::None &&
            field[2][0] == field[1][1] &&
            field[1][1] == field[0][2])
        {
            winner = field[2][0];
        }
    }
}

int State::minimax(int alpha, int beta)
{
    if (winner != Player::None)
    {
        return LOSS;
    }
    else if (moves == 9)
    {
        return DRAW;
    }

    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (field[column][row] == Player::None)
            {
                //Copy the whole state.
                State next_state = *this;
                Move move(column, row);
                //Execute the move.
                next_state.execute(move);
                //Call the minimax function on the new state.
                int score_next_state = -next_state.minimax(-beta, -alpha);

                if(score_next_state >= beta)
                {
                    // Oponent will avoid this position
                    return beta;
                }

                if (score_next_state > alpha)
                {
                    alpha = score_next_state;
                }
            }
        }
    }

    return alpha;
}

bool State::has_ended()
{
    //We have a winner or the whole field is filled, so we have a draw.
    return (winner != Player::None) || (moves == 9);
}

Player State::get_winner()
{
    return winner;
}

void State::read_move()
{
    //As long as we dont have a valid input we try ask the user for an input.
    while (true)
    {
        std::cout << "Enter square: ";
        std::string input;
        std::cin >> input;
        if (input.size() == 2) //Check if the input is in the right format.
        {
            int column = input[0] - 'a'; //Convert character to the position in the alphabet.
            int row = input[1] - '1';    //Convert numeric character to its value.

            if (column >= 0 && column < 3 && row >= 0 && row < 3) //Check if the position is on the field.
            {
                if (field[column][row] == Player::None) //Check if the position is empty.
                {
                    execute(Move(column, row)); //Execute the move.
                    break;                      //Break out of the while loop because we got a valid input.
                }
            }
        }
        std::cout << "Invalid input!" << std::endl;
    }
}

void State::generate_move()
{
    std::vector<Move> possible_moves;
    int best_score = LOSS;

    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (field[column][row] == Player::None) //Check if the move is possible.
            {
                Move move(column, row);
                State next_state = *this; //Copy the whole state
                next_state.execute(move); //Execute the move
                int score_next_state = -next_state.minimax(LOSS, WIN);

                if (score_next_state > best_score) //Check if we have a new best move.
                {
                    possible_moves.clear(); //Clear the vector because all moves saved are worse than the new move.
                    best_score = score_next_state;
                }
                if (score_next_state == best_score)
                {
                    possible_moves.push_back(move); //Add the move to the vector of equaly good moves.
                }
            }
        }
    }
    Move move = possible_moves[rand() % possible_moves.size()]; //Select a random move from the vector of the (equaly) best moves.
    std::cout << "Computer played: ";
    move.print(); //Print the move so you can see what the Ai played.
    std::cout << std::endl;
    execute(move);
}

void State::print()
{
    std::cout << "   ";
    for (int column = 0; column < 3; column++)
    {
        std::cout << " " << static_cast<char>('a' + column) << "  ";
    }
    std::cout << std::endl;
    print_empty_line();
    for (int row = 0; row < 3; row++)
    {
        std::cout << row + 1 << " ";
        print_line(row);
        print_empty_line();
    }
}

void State::print_empty_line()
{
    std::cout << "  +";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "---+";
    }
    std::cout << std::endl;
}

void State::print_line(int row)
{
    const static char player_chars[] = {' ', 'X', 'O'};
    std::cout << "|";
    for (int column = 0; column < 3; column++)
    {
        Player occupation = field[column][row];
        std::cout << " " << player_chars[static_cast<int>(occupation)] << " |";
    }
    std::cout << std::endl;
}
