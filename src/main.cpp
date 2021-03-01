#include <iostream>
#include "State.h"

int main()
{
    State state;
    //Print the initial state
    state.print();

    while (!state.has_ended())
    {
        //Read a move from the user.
        state.read_move();
        //Check if the game has ended.
        if (!state.has_ended())
        {
            //Execute a computer move.
            state.generate_move();
        }
        //Print the updated state.
        state.print();
    }

    Player winner = state.get_winner();

    switch (winner)
    {
    case Player::None:
        std::cout << "Draw!" << std::endl;
        break;
    case Player::Cross:
        std::cout << "Cross won!" << std::endl;
        break;
    case Player::Nought:
        std::cout << "Nought won!" << std::endl;
        break;
    }

    return 0;
}
