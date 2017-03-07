#include "Reinforcement.h"

#include <limits> //needed for numeric_limits
#include <cstdlib> //needed for rand()
#include <vector> //needed for vectors
#include <iostream> //needed for cout
#include <sstream> //needed of osstream
#include <fstream> //needed for saving the file
#include <math.h> //needed for log base 2


Reinforcement::Reinforcement(int Games, std::string saveName)
{
    //ctor
    Load(saveName);
    Learning(Games);
    Save(saveName); //these files can get "quite" big
}

Direction Reinforcement::GetMove(Board board)
{
    Direction direction[4] = {Up, Right, Down, Left};
    bool highest[4] = {false, false, false, false};
    double value= -1*std::numeric_limits<double>::max();
    //get the value of each move
    for (int i=0; i<4; i++)
    {
        if(board.CanMakeMove(direction[i]))
        {
            double tempValue = 0;
            if(Q.count(ToState(board,direction[i])))
            {
                tempValue = Q[ToState(board,direction[i])];
            }
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
    double lambda = 1; //discount factor, also set between 0 and 1
    //do reinforcement learning
    for(int i=0; i<Games; i++)
    {
        //play game
        Board board;
        while(board.CanMakeAMove())
        {
            //pick which move to make
            Direction nextMove = GreedyPolicy(board, 0.1);
            //store the current board
            std::bitset<66> state = ToState(board, nextMove);
            double reward = 0;
            for(int j=0; j<4; j++)
            {
                for(int k=0; k<4; k++)
                {
                    if(board.GetBoard(j,k)==0)
                    {
                        reward = reward + 1;
                    }
                }
            }
            //make move
            board.Move(nextMove);
            //update the value of Q(s,a), if Q(s,a) hasn't been picked before give it a default value (This is done in the max value function)
            if(Q.count(state)==0)
            {
                Q.insert({state,0});
            }
            Q[state] = Q[state] + alpha*(reward + lambda*MaxValue(board) - Q[state]);
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

std::bitset<66> Reinforcement::ToState(Board board, Direction direction)
{
    std::bitset<66> state;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            int pow2 = int(log2(board.GetBoard(i,j)));
            std::bitset<4> temp (pow2);
            int startPosition = 16*i + 4*j;
            for(int k=startPosition; k<startPosition+4; k++)
            {
                if(temp[k-startPosition])
                {
                    state.set(k); //need to make sure it works
                }
            }
        }
    }
    //last two bits of bitset indicate the direction
    switch (direction)
    {
    case Up:
        //both bits zero
        return state;
    case Right:
        //first bit one
        state.set(64);
        return state;
    case Down:
        //both bits one
        state.set(64);
        state.set(65);
        return state;
    case Left:
        //second bit one
        state.set(65);
        return state;
    }
    return state;
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
    //up
    if(board.CanMakeMove(Up))
    {
        std::bitset<66> state = ToState(board, Up);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
            directions.push_back(Up);
        }
        else
        {
            values.push_back(0); //initialised value of Q
            directions.push_back(Up);
        }
    }
    //right
    if(board.CanMakeMove(Right))
    {
        std::bitset<66> state = ToState(board, Right);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
            directions.push_back(Right);
        }
        else
        {
            values.push_back(0); //initialised value of Q
            directions.push_back(Right);
        }
    }
    //down
    if(board.CanMakeMove(Down))
    {
        std::bitset<66> state = ToState(board, Down);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
            directions.push_back(Down);
        }
        else
        {
            values.push_back(0); //initialised value of Q
            directions.push_back(Down);
        }
    }
    //left
    if(board.CanMakeMove(Left))
    {
        std::bitset<66> state = ToState(board, Left);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
            directions.push_back(Left);
        }
        else
        {
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
        return largest-2048;
    }
    //find the best value
    std::vector<double> values;
    //up
    if(board.CanMakeMove(Up))
    {
        std::bitset<66> state = ToState(board, Up);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
        }
        else
        {
            values.push_back(0); //initialised value of Q
        }
    }
    //right
    if(board.CanMakeMove(Right))
    {
        std::bitset<66> state = ToState(board, Right);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
        }
        else
        {
            values.push_back(0); //initialised value of Q
        }
    }
    //down
    if(board.CanMakeMove(Down))
    {
        std::bitset<66> state = ToState(board, Down);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
        }
        else
        {
            values.push_back(0); //initialised value of Q
        }
    }
    //left
    if(board.CanMakeMove(Left))
    {
        std::bitset<66> state = ToState(board, Left);
        if(Q.count(state)>0)
        {
            values.push_back(Q[state]);
        }
        else
        {
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
    //need to empty the file before I do anything to it
    std::ofstream file;
    file.open(saveName); //removes anything currently in the file
    //iterate through the list
    for( const auto& n : Q )
    {
        file << n.first << "," << n.second << ",\n";  //may need to be changed
    }
    file.close();
}

void Reinforcement::Load(std::string loadName)
{
    std::ifstream file;
    file.open(loadName);
    //assuming there is a file to load
    if(file.is_open())
    {
        std::string line;
        //go through each line adding the key and value
        while(getline(file,line))
        {
            std::string strings[2];
            std::stringstream ss(line);
            int i = 0;
            std::string token;
            //split the string
            while(getline(ss,token,',') and i<2)
            {
                strings[i]=token;
                i++;
            }
            std::bitset<66> key (strings[0]);
            double value = atof(strings[1].c_str());
            Q.insert({key,value});
        }
        file.close();
    }
    //need to make sure this is doing what I expect
    /*
    for( const auto& n : Q )
    {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    */
}
