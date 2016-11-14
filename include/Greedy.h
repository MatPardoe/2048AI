#ifndef GREEDY_H
#define GREEDY_H

#include <Board.h>
#include <Evaluation.h>

class Greedy : public Evaluation
{
    public:
        Greedy();
        double Evaluate(Board board);
    protected:
    private:
};

#endif // GREEDY_H
