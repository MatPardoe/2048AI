#include "RandomDirection.h"
#include <cstdlib>

RandomDirection::RandomDirection()
{
    choices[0] = Up;
    choices[1] = Right;
    choices[2] = Down;
    choices[3] = Left;
}

Direction RandomDirection::GetMove(Board board)
{
    Direction choice = choices[rand()%4];
    while (!board.CanMakeMove(choice))
    {
        choice = choices[rand()%4];
    }
    return choice;
}
