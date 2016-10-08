#include <cstdlib>
#include <time.h>
#include <iostream>

#include "Board.h"

// constructors

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


    int x = rand()%4;
    int y = rand()%4;
    while(board[x][y] != 0)
    {
        x = rand()%4;
        y = rand()%4;
    }
    if (rand()%10 == 1) //using chance from actual game of 1 in 10 for it to be a four
    {
        board[x][y] = 4;
    }
    else
    {
        board[x][y] = 2;
    }
    while(board[x][y] != 0)
    {
        x = rand()%4;
        y = rand()%4;
    }
    if (rand()%10 == 1) //using chance from actual game of 1 in 10 for it to be a four
    {
        board[x][y] = 4;
    }
    else
    {
        board[x][y] = 2;
    }

    score = 0;
    moves = 0;
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

//public methods

int Board::GetScore()
{
    return score;
}

void Board::Move(Direction direction)
{
    if (!CanMakeMove(direction))
    {
        return;
    }
    MakeMove(direction);
    moves++;
    int x = rand()%4;
    int y = rand()%4;
    while(board[x][y] != 0)
    {
        x = rand()%4;
        y = rand()%4;
    }
    if (rand()%10 == 1) //using chance from actual game of 1 in 10 for it to be a four
    {
        board[x][y] = 4;
        return;
    }
    board[x][y] = 2;
}

void Board::MakeMove(Direction direction)
{
    switch (direction)
    {
    case Up:
        MakeUpMove();
        break;
    case Right:
        MakeRightMove();
        break;
    case Down:
        MakeDownMove();
        break;
    case Left:
        MakeLeftMove();
        break;
    }
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

int Board::GetBoard(int i, int j)
{
    return board[i][j];
}

int Board::EndGame()
{
    throw "not yet implemented";
}

// private methods

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
    for (int i = 0; i < 4; i++)
    {
        // combine the tiles that are the same and next to each other
        for (int j = 0; j < 3; j++)
        {
            if (board[j][i] != 0 && board[j+1][i] == board[j][i])
            {
                board[j][i] = 2*board[j][i];
                score = score + board[j][i];
                board[j+1][i] = 0;
            }
        }
        // sliding the tiles across as expected
        for (int j = 1; j < 4; j++)
        {
            if (board[j][i] != 0)
            {
                for (int k = j; k > 0; k--)
                {
                    if (board[k-1][i] == 0)
                    {
                        board[k-1][i] = board[k][i];
                        board[k][i] = 0;
                    }
                }
            }
        }
    }
}

void Board::MakeRightMove()
{
    for (int i = 0; i < 4; i++)
    {
        // combine the tiles that are the same and next to each other
        for (int j = 3; j > 0; j--)
        {
            if (board[i][j] != 0 && board[i][j-1] == board[i][j])
            {
                board[i][j] = 2*board[i][j];
                score = score + board[i][j];
                board[i][j-1] = 0;
            }
        }
        // sliding the tiles across as expected
        for (int j = 2; j > -1; j--)
        {
            if (board[i][j] != 0)
            {
                for (int k = j; k < 3; k++)
                {
                    if (board[i][k+1] == 0)
                    {
                        board[i][k+1] = board[i][k];
                        board[i][k] = 0;
                    }
                }
            }
        }
    }
}

void Board::MakeDownMove()
{
    for (int i = 0; i < 4; i++)
    {
        // combine the tiles that are the same and next to each other
        for (int j = 3; j > 0; j--)
        {
            if (board[j][i] != 0 && board[j-1][i] == board[j][i])
            {
                board[j][i] = 2*board[j][i];
                score = score + board[j][i];
                board[j-1][i] = 0;
            }
        }
        // sliding the tiles across as expected
        for (int j = 2; j > -1; j--)
        {
            if (board[j][i] != 0)
            {
                for (int k = j; k < 3; k++)
                {
                    if (board[k+1][i] == 0)
                    {
                        board[k+1][i] = board[k][i];
                        board[k][i] = 0;
                    }
                }
            }
        }
    }
}

void Board::MakeLeftMove()
{
    for (int i = 0; i < 4; i++)
    {
        // combine the tiles that are the same and next to each other
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 0 && board[i][j+1] == board[i][j])
            {
                board[i][j] = 2*board[i][j];
                score = score + board[i][j];
                board[i][j+1] = 0;
            }
        }
        // sliding the tiles across as expected
        for (int j = 1; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                for (int k = j; k > 0; k--)
                {
                    if (board[i][k-1] == 0)
                    {
                        board[i][k-1] = board[i][k];
                        board[i][k] = 0;
                    }
                }
            }
        }
    }
}
