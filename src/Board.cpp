#include <cstdlib>
#include <time.h>
#include <iostream>

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
    score = currentScore;
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
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
    switch (direction)
    {
    case Up:
        return CanMakeUpMove();
        break;
    case Right:
        return CanMakeRightMove();
        break;
    case Down:
        return CanMakeDownMove();
        break;
    case Left:
        return CanMakeLeftMove();
        break;
    }
    return false;
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
    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<4; j++)
        {
            std::cout << board[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

void Board::AddTile(int i, int j, int value)
{
    board[i][j] = value;
}

int Board::EndGame()
{
    throw "not yet implemented";
}

// here onwards private functions

bool Board::CanMakeUpMove()
{
    for (int i = 0; i<4; i++)
    {
        bool noneZero = false;
        int lastValue = 0;
        for (int j = 3; j<-1; j--)
        {
            if (noneZero)
            {
                if (lastValue == board[j][i])
                {
                    return true;
                }
                if (board[j][i] == 0)
                {
                    return true;
                }
                lastValue = board[j][i];
            }
            else
            {
                if (board[j][i] != 0)
                {
                    noneZero = true;
                }
                lastValue = board[j][i];
            }
        }
    }
    return false;
}

bool Board::CanMakeRightMove()
{
    for (int i = 0; i<4; i++)
    {
        bool noneZero = false;
        int lastValue = 0;
        for (int j = 0; j<4; j++)
        {
            if (noneZero)
            {
                if (lastValue == board[i][j])
                {
                    return true;
                }
                if (board[i][j] == 0)
                {
                    return true;
                }
                lastValue = board[i][j];
            }
            else
            {
                if (board[i][j] != 0)
                {
                    noneZero = true;
                }
                lastValue = board[i][j];
            }
        }
    }
    return false;
}

bool Board::CanMakeDownMove()
{
    for (int i = 0; i<4; i++)
    {
        bool noneZero = false;
        int lastValue = 0;
        for (int j = 0; j<4; j++)
        {
            if (noneZero)
            {
                if (lastValue == board[j][i])
                {
                    return true;
                }
                if (board[j][i] == 0)
                {
                    return true;
                }
                lastValue = board[j][i];
            }
            else
            {
                if (board[j][i] != 0)
                {
                    noneZero = true;
                }
                lastValue = board[j][i];
            }
        }
    }
    return false;
}

bool Board::CanMakeLeftMove()
{
    for (int i = 0; i<4; i++)
    {
        bool noneZero = false;
        int lastValue = 0;
        for (int j = 3; j<-1; j--)
        {
            if (noneZero)
            {
                if (lastValue == board[i][j])
                {
                    return true;
                }
                if (board[i][j] == 0)
                {
                    return true;
                }
                lastValue = board[i][j];
            }
            else
            {
                if (board[i][j] != 0)
                {
                    noneZero = true;
                }
                lastValue = board[i][j];
            }
        }
    }
    return false;
}

void Board::MakeUpMove()
{
    throw "not yet implemented";
}

void Board::MakeRightMove()
{
    throw "not yet implemented";
}

void Board::MakeDownMove()
{
    throw "not yet implemented";
}

void Board::MakeLeftMove()
{
    throw "not yet implemented";
}
