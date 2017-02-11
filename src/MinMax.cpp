#include "MinMax.h"
#include "stdio.h"
#include <iostream>

/*
node struct defined in the MinMax.h file here simply as a reminder
struct node
{
    Board currentBoard; // the board state at this move
    double heuristicValue; // the rating of the board position, either by the best of the children or calculated if it is a leaf
    // all node pointers default to zero so I know not to use them
    node *upNode = 0;
    node *rightNode = 0;
    node *downNode = 0;
    node *leftNode = 0;
};
*/


MinMax::MinMax(int depth, Evaluation* evaluationFunction)
{
    treeDepth = depth;
    evaluation = evaluationFunction;
}

Direction MinMax::GetMove(Board board)
{
    node* root = new node;
    Board tempBoard(board);
    (*root).currentBoard = tempBoard;
    MakeTree((*root),treeDepth);
    CalculateHeuristics((*root));

    // find which of the children is the best node
    //up
    if ((*root).upNode != 0)
    {
        if ((*root).heuristicValue == (*(*root).upNode).heuristicValue)
        {
            DeleteTree((*root));
            return Up;
        }
    }
    //right
    if ((*root).rightNode != 0)
    {
        if ((*root).heuristicValue == (*(*root).rightNode).heuristicValue)
        {
            DeleteTree((*root));
            return Right;
        }
    }
    //down
    if ((*root).downNode != 0)
    {
        if ((*root).heuristicValue == (*(*root).downNode).heuristicValue)
        {
            DeleteTree((*root));
            return Down;
        }
    }
    //if it hasn't been any of the above values it must be the left one
    DeleteTree((*root));;
    return Left;
}

void MinMax::MakeTree(node& root, int depth)
{
    if (depth == 0)
    {
        return;
    }
    depth--;
    //add child nodes

    //up
    if(root.currentBoard.CanMakeMove(Up))
    {
        root.upNode = new node;
        (*root.upNode).currentBoard = Move(root.currentBoard, Up);
        MakeTree((*root.upNode),depth);
    }
    //right
    if(root.currentBoard.CanMakeMove(Right))
    {
        root.rightNode = new node;
        (*root.rightNode).currentBoard = Move(root.currentBoard, Right);
        MakeTree((*root.rightNode),depth);
    }
    //down
    if(root.currentBoard.CanMakeMove(Down))
    {
        root.downNode = new node;
        (*root.downNode).currentBoard = Move(root.currentBoard, Down);
        MakeTree((*root.downNode),depth);
    }
    //left
    if(root.currentBoard.CanMakeMove(Left))
    {
        root.leftNode = new node;
        (*root.leftNode).currentBoard = Move(root.currentBoard, Left);
        MakeTree((*root.leftNode),depth);
    }
}

Board MinMax::Move(Board board, Direction Move)
{
    board.MakeMove(Move);
    int minX = 0;
    int minY = 0;
    int minAverageScore = 0;

    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            if(board.GetBoard(x,y) == 0)
            {
                board.AddTile(x,y,2);

                int tempAverage = 0;
                int movesCount = 0;
                //test out each move
                if(board.CanMakeMove(Up))
                {
                    Board tempBoard(board);
                    tempBoard.MakeMove(Up);
                    movesCount++;
                    tempAverage = tempAverage + tempBoard.GetScore();
                }
                if(board.CanMakeMove(Right))
                {
                    Board tempBoard(board);
                    tempBoard.MakeMove(Right);
                    movesCount++;
                    tempAverage = tempAverage + tempBoard.GetScore();
                }
                if(board.CanMakeMove(Down))
                {
                    Board tempBoard(board);
                    tempBoard.MakeMove(Down);
                    movesCount++;
                    tempAverage = tempAverage + tempBoard.GetScore();
                }
                if(board.CanMakeMove(Left))
                {
                    Board tempBoard(board);
                    tempBoard.MakeMove(Left);
                    movesCount++;
                    tempAverage = tempAverage + tempBoard.GetScore();
                }

                if(movesCount != 0)
                {
                    tempAverage = tempAverage/movesCount; //will result in an integer whatever, but different positions should give different enough scores that it doesn't matter
                } else
                {
                    tempAverage = -1;
                }

                if(tempAverage < minAverageScore or minAverageScore == 0)
                {
                    minAverageScore = tempAverage;
                    minX = x;
                    minY = y;
                }

                board.AddTile(x,y,0);
            }
        }
    }
    board.AddTile(minX,minY,2);
    return board;
}

void MinMax::CalculateHeuristics(node& root)
{
    bool valueFound = false;

    // up
    if(root.upNode != 0)
    {
        CalculateHeuristics(*root.upNode);
        if (valueFound == false)
        {
            root.heuristicValue = (*root.upNode).heuristicValue;
        }
        else if(root.heuristicValue < (*root.upNode).heuristicValue)
        {
            root.heuristicValue = (*root.upNode).heuristicValue;
        }
        valueFound = true;
    }
    //right
    if(root.rightNode != 0)
    {
        CalculateHeuristics(*root.rightNode);
        if (valueFound == false)
        {
            root.heuristicValue = (*root.rightNode).heuristicValue;
        }
        else if(root.heuristicValue < (*root.rightNode).heuristicValue)
        {
            root.heuristicValue = (*root.rightNode).heuristicValue;
        }
        valueFound = true;
    }
    //down
    if(root.downNode != 0)
    {
        CalculateHeuristics(*root.downNode);
        if (valueFound == false)
        {
            root.heuristicValue = (*root.downNode).heuristicValue;
        }
        else if(root.heuristicValue < (*root.downNode).heuristicValue)
        {
            root.heuristicValue = (*root.downNode).heuristicValue;
        }
        valueFound = true;
    }
    //left
    if(root.leftNode != 0)
    {
        CalculateHeuristics(*root.leftNode);
        if (valueFound == false)
        {
            root.heuristicValue = (*root.leftNode).heuristicValue;
        }
        else if(root.heuristicValue < (*root.leftNode).heuristicValue)
        {
            root.heuristicValue = (*root.leftNode).heuristicValue;
        }
        valueFound = true;
    }

    //if there are no child nodes calculate the heuristic value of the node from the current board
    if (valueFound == false)
    {
        root.heuristicValue = (*evaluation).Evaluate(root.currentBoard);
    }
}

void MinMax::DeleteTree(node& root)
{
    if (root.upNode != 0)
    {
        DeleteTree(*(root.upNode));
    }
    if (root.rightNode != 0)
    {
        DeleteTree(*(root.rightNode));
    }
    if (root.downNode != 0)
    {
        DeleteTree(*(root.downNode));
    }
    if (root.leftNode != 0)
    {
        DeleteTree(*(root.leftNode));
    }
    delete &root;
}
