#include "ExpectiMax.h"

/*
expectiNode struct defined in the ExpectiMax.h file here simply as a reminder
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
    std::vector<*expectiNode> chanceNodeList;
};
*/

ExpectiMax::ExpectiMax(int depth, Evaluation* evaluationFunction)
{
    treeDepth = depth;
    evaluation = evaluationFunction;
}

Direction ExpectiMax::GetMove(Board board)
{
    expectiNode root;
    Board tempBoard(board);
    root.currentBoard = tempBoard;
    root.ChanceNode = true;
    MakeTree(root,treeDepth);
    CalculateHeuristics(root);

    // find which of the children is the best node
    //up
    if (root.upNode != 0)
    {
        if (root.heuristicValue == (*root.upNode).heuristicValue)
        {
            DeleteTree(root);
            return Up;
        }
    }
    //right
    if (root.rightNode != 0)
    {
        if (root.heuristicValue == (*root.rightNode).heuristicValue)
        {
            DeleteTree(root);
            return Right;
        }
    }
    //down
    if (root.downNode != 0)
    {
        if (root.heuristicValue == (*root.downNode).heuristicValue)
        {
            DeleteTree(root);
            return Down;
        }
    }
    //if it hasn't been any of the above values it must be the left one
    DeleteTree(root);
    return Left;
}

void ExpectiMax::MakeTree(expectiNode& root, int depth)
{
    if(root.ChanceNode)
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
            root.upNode = new expectiNode;
            Board temp = root.currentBoard;
            temp.MakeMove(Up);
            (*root.upNode).currentBoard = temp;
            (*root.upNode).ChanceNode = false;
            MakeTree((*root.upNode),depth);
        }
        //right
        if(root.currentBoard.CanMakeMove(Right))
        {
            root.rightNode = new expectiNode;
            Board temp = root.currentBoard;
            temp.MakeMove(Right);
            (*root.rightNode).currentBoard = temp;
            (*root.rightNode).ChanceNode = false;
            MakeTree((*root.rightNode),depth);
        }
        //down
        if(root.currentBoard.CanMakeMove(Down))
        {
            root.downNode = new expectiNode;
            Board temp = root.currentBoard;
            temp.MakeMove(Down);
            (*root.downNode).currentBoard = temp;
            (*root.downNode).ChanceNode = false;
            MakeTree((*root.downNode),depth);
        }
        //left
        if(root.currentBoard.CanMakeMove(Left))
        {
            root.leftNode = new expectiNode;
            Board temp = root.currentBoard;
            temp.MakeMove(Left);
            (*root.leftNode).currentBoard = temp;
            (*root.leftNode).ChanceNode = false;
            MakeTree((*root.leftNode),depth);
        }
    }
    else
    {
        int numEmpty = 0;
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                numEmpty++;
            }
        }
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                root.chanceNodeList.push_back(new expectiNode);
                //this now has to deal with the new expectiNode that has been created in the same way as above
                Board temp = root.currentBoard;
                temp.AddTile(i,j,2);
                (*root.chanceNodeList.back()).currentBoard = temp;
                (*root.chanceNodeList.back()).Chance = 1.0/numEmpty;
                (*root.chanceNodeList.back()).ChanceNode = true;
                MakeTree((*root.chanceNodeList.back()),depth);
            }
        }
    }
}

void ExpectiMax::CalculateHeuristics(expectiNode& root)
{

}

void ExpectiMax::DeleteTree(expectiNode& root)
{
    //delete specific nodes
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
    // delete any nodes in the vector
    while(not root.chanceNodeList.empty())
    {
        DeleteTree(*root.chanceNodeList.back());
        root.chanceNodeList.pop_back();
    }

    delete &root;
}
