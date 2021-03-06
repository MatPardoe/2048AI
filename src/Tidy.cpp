#include "Tidy.h"
#include <math.h>
#include <stdlib.h>

Tidy::Tidy()
{
    //ctor
}

double Tidy::Evaluate(Board board)
{
    double value = 0;
    //count the number of empty tiles
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(board.GetBoard(i,j) == 0)
            {
                value = value + 10;
            }
        }
    }

    //find the smoothness (lower numbers = smoother)
    int smoothness = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(board.GetBoard(i,j)!=0)
            {
                //using the log base 2 value of the tiles,
                //since this way difference between board tiles can be counted in individual numbers (e.g. 2=1, 4=2, 8=3, 16=4, 32=5, etc ...)
                int currentTileLogged = log2(board.GetBoard(i,j));
                //if statements are in place just to avoid trying to access values outside the board
                //and to avoid trying to do log(0)
                if(i != 0)
                {
                    if(board.GetBoard(i-1,j) != 0)
                    {
                        smoothness = smoothness + abs(currentTileLogged-log2(board.GetBoard(i-1,j)));
                    }
                }
                if(i != 3)
                {
                    if(board.GetBoard(i+1,j) != 0)
                    {
                        smoothness = smoothness + abs(currentTileLogged-log2(board.GetBoard(i+1,j)));
                    }
                }
                if(j != 0)
                {
                    if(board.GetBoard(i,j-1) != 0)
                    {
                        smoothness = smoothness + abs(currentTileLogged-log2(board.GetBoard(i,j-1)));
                    }
                }
                if(j != 3)
                {
                    if(board.GetBoard(i,j+1) != 0)
                    {
                        smoothness = smoothness + abs(currentTileLogged-log2(board.GetBoard(i,j+1)));
                    }
                }
            }
        }
    }

    return value/smoothness;
}
