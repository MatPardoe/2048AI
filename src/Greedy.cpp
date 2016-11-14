#include "Greedy.h"

Greedy::Greedy()
{
    //ctor
}

double Greedy::Evaluate(Board board)
{
    return board.GetScore();
}
