#include "Positional.h"
#include <math.h>

Positional::Positional()
{
    //ctor
}

double Positional::Evaluate(Board board)
{
    double value = board.GetScore();
    //go through all four columns/rows
    for(int i = 0; i < 4; i++)
    {
        //setup variables
        int acrossValue = board.GetBoard(i,0);
        int downValue = board.GetBoard(0,i);
        int acrossLargest = board.GetBoard(i,0);
        int downLargest = board.GetBoard(0,i);
        bool acrossLarger = true;
        bool acrossSmaller = true;
        bool downLarger = true;
        bool downSmaller = true;
        // go through the cells of the column/row and check them for monoticity
        // counting cells being equal as monotonic in both directions as need to be the same value to be able to combine them
        for(int j = 1; j < 4; j++)
        {
            //finding the biggest value in the column/row
            if(board.GetBoard(i,j) > acrossLargest)
            {
                acrossLargest = board.GetBoard(i,j);
            }
            if(board.GetBoard(j,i) > downLargest)
            {
                downLargest = board.GetBoard(j,i);
            }

            if(board.GetBoard(i,j) != 0 and acrossValue != 0 and board.GetBoard(i,j) != acrossValue) //if the tile is 0 then it is empty so is neither larger or smaller
            {
                if(board.GetBoard(i,j) > acrossValue)
                {
                    acrossSmaller = false;
                }
                else
                {
                    acrossLarger = false;
                }
            }

            if(board.GetBoard(j,i) != 0 and downValue != 0 and board.GetBoard(j,i) != downValue) //same argument as above if statement
            {
                if(board.GetBoard(j,i) > downValue)
                {
                    downSmaller = false;
                }
                else
                {
                    downLarger = false;
                }
            }

            acrossValue = board.GetBoard(i,j);
            downValue = board.GetBoard(j,i);
        }
        //update score based on monoticity of the current rows using xor because if both at most two tiles in row not next to each other (adds risk as could be filled by a 2 or 4
        if(acrossLarger xor acrossSmaller)
        {
            value = value * log(acrossLargest);
        }
        if(downLarger xor downSmaller)
        {
            value = value * log(downLargest);
        }

        if(!(acrossLarger or acrossSmaller))
        {
            value = value / log(acrossLargest);
        }
        if(!(downLarger or downSmaller))
        {
            value = value / log(downLargest);
        }
    }

    //increase boards value if the biggest piece is in a corner, or at least on the edge
    int maxX = 0;
    int maxY = 0;
    int maxValue = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(board.GetBoard(i,j) > maxValue)
            {
                maxValue = board.GetBoard(i,j);
                maxX=i;
                maxY=j;
            }
        }
    }

    //0 and 3 represent the edges of the 4 by 4 grid
    if(maxX == 0 or maxX == 3)
    {
        value = value*log(maxValue);
    }

    if(maxY == 0 or maxY == 3)
    {
        value = value*log(maxValue);
    }
    return value;
}
