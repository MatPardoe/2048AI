#ifndef REINFORCEMENT_H
#define REINFORCEMENT_H

#include <Controler.h>
#include <Board.h>

#include <unordered_map>
#include <iostream>


class Reinforcement : public Controler
{
    public:
        Reinforcement(int Games, std::string saveName);
        Direction GetMove(Board board);
    protected:
    private:
        void Learning(int Games);
        std::string Board2String(Board board);
        std::string Direction2String(Direction direction);
        double MaxValue(Board board);
        Direction GreedyPolicy(Board board, double epsilon);
        void Save(std::string saveName);
        //variables
        //NO IDEA HOW I AM GOING TO STORE STUFF, maybe using a unorderedmap
        std::unordered_map<std::string,int> Q;

};

#endif // REINFORCEMENT_H
