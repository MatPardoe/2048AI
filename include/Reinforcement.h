#ifndef REINFORCEMENT_H
#define REINFORCEMENT_H

#include <Controler.h>
#include <Board.h>

#include <unordered_map>
#include <iostream>
#include <bitset>


class Reinforcement : public Controler
{
    public:
        Reinforcement(int Games, std::string saveName);
        Direction GetMove(Board board);
    protected:
    private:
        void Learning(int Games);
        std::bitset<66> ToState(Board board, Direction direction); //change this
        double MaxValue(Board board);
        Direction GreedyPolicy(Board board, double epsilon);
        void Save(std::string saveName);
        void Load(std::string loadName);
        //variables
        std::unordered_map<std::bitset<66>,int> Q;

};

#endif // REINFORCEMENT_H
