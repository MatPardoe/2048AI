#ifndef MINMAX_H
#define MINMAX_H

#include <Controler.h>
#include <Board.h>

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


class MinMax : public Controler
{
    public:
        MinMax(int depth);
        Direction GetMove(Board board);
    protected:
    private:
        void MakeTree(node& root, int depth);
        Board Move(Board board, Direction Move);
        void CalculateHeuristics(node& root);
        void DeleteTree(node& root);
        double EvaluationFunction(Board board);
        //variables
        int treeDepth;
};

#endif // MINMAX_H
