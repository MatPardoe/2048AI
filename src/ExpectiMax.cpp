#include "ExpectiMax.h"

ExpectiMax::ExpectiMax(int depth, Evaluation* evaluationFunction)
{
    treeDepth = depth;
    evaluation = evaluationFunction;
}

Direction ExpectiMax::GetMove()
{
    return Direction.Up;
}

void ExpectiMax::MakeTree(expectNode& root, int depth)
{

}

Board Move(Board board, Direction Move)
{
    Board board;
    return board
}

void CalculateHeuristics(expectNode& root)
{

}

void DeleteTree(expectiNode& root)
{

}
