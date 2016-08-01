#include <cstdlib>
#include <time.h>

#include "Board.h"



Board::Board()
{
    int i;
    int j;
    for(i = 0; i<4; i++)
    {
        for (j = 0; j<4; j++)
        {
            board[i][j] = 0;
        }
    }
    score = 0;
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
}

Board::Board(int currentBoard[4][4], int currentScore)
{
    int i;
    int j;
    for (i = 0; i<4; i++)
    {
        for (j = 0; j<4; j++)
        {
            board[i][j] = currentBoard[i][j];
        }
    }
}

int Board::GetScore()
{
    return score;
}

void Board::MakeMove(Direction direction)
{
    throw "not yet implemented";
}

bool Board::CanMakeMove(Direction direction)
{
    throw "not yet implemented";
}

bool Board::CanMakeAMove()
{
    if (CanMakeUpMove())
    {
        return true;
    }
    if (CanMakeRightMove())
    {
        return true;
    }
    if (CanMakeDownMove())
    {
        return true;
    }
    if (CanMakeLeftMove())
    {
        return true;
    }
    return false;
}

void Board::DisplayBoard()
{
    throw "not yet implemented";
}

void Board::AddTile()
{
    throw "not yet implemented";
}

int Board::EndGame()
{
    throw "not yet implemented";
}

bool Board::CanMakeUpMove()
{
    throw "not yet implemented";
}

bool Board::CanMakeRightMove()
{
    throw "not yet implemented";
}

bool Board::CanMakeDownMove()
{
    throw "not yet implemented";
}

bool Board::CanMakeLeftMove()
{
    throw "not yet implemented";
}
