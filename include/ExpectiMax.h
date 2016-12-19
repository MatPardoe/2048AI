#ifndef EXPECTIMAX_H
#define EXPECTIMAX_H

#include <Controler.h>
#include <Board.h>
#include <Evaluation.h>
#include <vector>

struct expectiNode
{
    bool ChanceNode;
    double Chance;
    Board currentBoard; // the board state at this move
    double heuristicValue; // the rating of the board position, either by the best of the children or calculated if it is a leaf
    // all node pointers default to zero so I know not to use them
    expectiNode *upNode = 0;
    expectiNode *rightNode = 0;
    expectiNode *downNode = 0;
    expectiNode *leftNode = 0;
    std::vector<expectiNode *> chanceNodeList;
};


class ExpectiMax : public Controler
{
    public:
        ExpectiMax(int depth, Evaluation* evaluationFunction);
        Direction GetMove(Board board);
    protected:
    private:
        void MakeTree(expectiNode& root, int depth);
        void CalculateHeuristics(expectiNode& root);
        void DeleteTree(expectiNode& root);
        //variables
        int treeDepth;
        Evaluation* evaluation;
};

#endif // EXPECTIMAX_H
