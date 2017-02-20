#include "Reinforcement.h"

#include <limits> //needed for numeric_limits
#include <cstdlib> //needed for rand()
#include <vector> //needed for vectors
#include <iostream> //needed for cout
#include <sstream> //needed of osstream
#include <fstream> //needed for saving the file

Reinforcement::Reinforcement(int Games, std::string saveName)
{
    //ctor
    Learning(Games);
    Save(saveName);
}

Direction Reinforcement::GetMove(Board board)
{
    //the value is currently always set to zero
    //once I have worked out how I am storing the Q value
    //of each state I will be setting the value using that
    Direction direction[4] = {Up, Right, Down, Left};
    bool highest[4] = {false, false, false, false};
    double value= -1*std::numeric_limits<double>::min();
    //get the value of each move
    for (int i=0; i<4; i++)
    {
        if(board.CanMakeMove(direction[i]))
        {
            double tempValue = 0.0;
            if(tempValue>value)
            {
                for(int j=0; j<i; j++)
                {
                    highest[j] = false;
                }
                highest[i] = true;
                value = tempValue;
            }
            if(tempValue == value)
            {
                highest[i] = true;
            }
        }
    }
    int highestCount = 0;
    int location = 0;
    for (int i=0; i<4; i++)
    {
        if(highest[i])
        {
            highestCount++;
            location = i;

        }
    }
    if(highestCount == 1)
    {
        return direction[location];
    }
    location = rand()%4;
    while(not highest[location])
    {
        location = rand()%4;
    }
    return direction[location];
}

/**
Initialise Q
for each game
start create the board object giving the initial state
then for each move
record the current state (s)
select the action (a) using the policy decided (e.g. greedy)
take the action
record the new state (s') and the reward (r)
do calculations to update the value of Q(s,a)
*/
void Reinforcement::Learning(int Games)
{
    double alpha = 0.5; //the learning rate, set between 0 and 1
    double lambda = 0.5; //discount factor, also set between 0 and 1
    //do reinforcement learning
    for(int i=0; i<Games; i++)
    {
        int moves = 0;
        //play game
        Board board;
        while(board.CanMakeAMove())
        {
            moves++;
            //store the current board
            std::string state = Board2String(board);
            //pick which move to make TODO: this bit
            Direction nextMove = GreedyPolicy(board, 0.9);
            //make move
            board.Move(nextMove);
            //record new data
            double reward = moves;
            //update the value of Q(s,a), if Q(s,a) hasn't been picked before give it a default value (This is done in the max value function)
            if(Q.count(state+Direction2String(nextMove))==0)
            {
                Q.insert({state+Direction2String(nextMove),0});
            }
            Q[state+Direction2String(nextMove)] = Q[state+Direction2String(nextMove)] + alpha*(reward + lambda*MaxValue(board) - Q[state+Direction2String(nextMove)]);
        }
        if(i%100 == 0)
        {
            std::cout << "played " << (i*100.0)/Games << "% of games" << std::endl;
        }
    }
    /*
    for( const auto& n : Q )
    {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    */
}

std::string Reinforcement::Board2String(Board board)
{
    std::string boardString = "";
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            std::ostringstream convert;
            convert << board.GetBoard(i,j);
            boardString = boardString + convert.str();
        }
    }
    return boardString;
}

std::string Reinforcement::Direction2String(Direction direction)
{
    switch (direction)
    {
    case Up:
        return "Up";
    case Right:
        return "Right";
    case Down:
        return "Down";
    case Left:
        return "Left";
    default:
        return "No Direction";
    }
}

Direction Reinforcement::GreedyPolicy(Board board, double epsilon)
{
    //decide whether to pick randomly or not
    if((rand()/((double)RAND_MAX)) < epsilon)
    {
        Direction direction[4] = {Up,Right,Left,Down};
        Direction pick = direction[rand()%4];
        while(not board.CanMakeMove(pick))
        {
            pick = direction[rand()%4];
        }
        return pick;
    }

    std::vector<double> values;
    std::vector<Direction> directions;
    std::string boardString = Board2String(board);
    //up
    if(board.CanMakeMove(Up))
    {
        if(Q.count(boardString+Direction2String(Up))>0)
        {
            values.push_back(Q[boardString+Direction2String(Up)]);
            directions.push_back(Up);
        }
        else
        {
            Q.insert({boardString+Direction2String(Up),0});
            values.push_back(0); //initialised value of Q
            directions.push_back(Up);
        }
    }
    //right
    if(board.CanMakeMove(Right))
    {
        if(Q.count(boardString+Direction2String(Right))>0)
        {
            values.push_back(Q[boardString+Direction2String(Right)]);
            directions.push_back(Right);
        }
        else
        {
            Q.insert({boardString+Direction2String(Right),0});
            values.push_back(0); //initialised value of Q
            directions.push_back(Right);
        }
    }
    //down
    if(board.CanMakeMove(Down))
    {
        if(Q.count(boardString+Direction2String(Down))>0)
        {
            values.push_back(Q[boardString+Direction2String(Down)]);
            directions.push_back(Down);
        }
        else
        {
            Q.insert({boardString+Direction2String(Down),0});
            values.push_back(0); //initialised value of Q
            directions.push_back(Down);
        }
    }
    //left
    if(board.CanMakeMove(Left))
    {
        if(Q.count(boardString+Direction2String(Left))>0)
        {
            values.push_back(Q[boardString+Direction2String(Left)]);
            directions.push_back(Left);
        }
        else
        {
            Q.insert({boardString+Direction2String(Left),0});
            values.push_back(0); //initialised value of Q
            directions.push_back(Left);
        }
    }

    Direction directionPick = directions[0];
    double maxValue = values[0];
    for(int i=1; (unsigned)i<directions.size(); i++)
    {
        if(values[i]>maxValue)
        {
            maxValue = values[i];
            directionPick = directions[i];
        }
    }
    return directionPick;
}

double Reinforcement::MaxValue(Board board)
{
    //need to handle when board is at the end of a game maybe give a score based on the largest tile - 2048
    if(not board.CanMakeAMove())
    {
        int largest = 0;
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                if(board.GetBoard(i,j)>largest)
                {
                    largest = board.GetBoard(i,j);
                }
            }
        }
        return largest-1024;
    }
    //find the best value
    std::string boardString = Board2String(board);
    std::vector<double> values;
    //up
    if(board.CanMakeMove(Up))
    {
        if(Q.count(boardString+Direction2String(Up))>0)
        {
            values.push_back(Q[boardString+Direction2String(Up)]);
        }
        else
        {
            Q.insert({boardString+Direction2String(Up),0});
            values.push_back(0); //initialised value of Q
        }
    }
    //right
    if(board.CanMakeMove(Right))
    {
        if(Q.count(boardString+Direction2String(Right))>0)
        {
            values.push_back(Q[boardString+Direction2String(Right)]);
        }
        else
        {
            Q.insert({boardString+Direction2String(Right),0});
            values.push_back(0); //initialised value of Q
        }
    }
    //down
    if(board.CanMakeMove(Down))
    {
        if(Q.count(boardString+Direction2String(Down))>0)
        {
            values.push_back(Q[boardString+Direction2String(Down)]);
        }
        else
        {
            Q.insert({boardString+Direction2String(Down),0});
            values.push_back(0); //initialised value of Q
        }
    }
    //left
    if(board.CanMakeMove(Left))
    {
        if(Q.count(boardString+Direction2String(Left))>0)
        {
            values.push_back(Q[boardString+Direction2String(Left)]);
        }
        else
        {
            Q.insert({boardString+Direction2String(Left),0});
            values.push_back(0); //initialised value of Q
        }
    }

    double maxValue = values[0];
    for(int i=1; (unsigned)i<values.size(); i++)
    {
        if(values[i]>maxValue)
        {
            maxValue = values[i];
        }
    }
    return maxValue;
}

void Reinforcement::Save(std::string saveName)
{
    std::ofstream file;
    file.open(saveName);
    //iterate through the list
    file << "words,\n";
    for( const auto& n : Q )
    {
        file << n.first << "," << n.second << ",\n";
    }
    file.close();
}
