#ifndef SMOOTHGREEDY_H
#define SMOOTHGREEDY_H

#include <Board.h>
#include <Evaluation.h>

class SmoothGreedy : public Evaluation
{
    public:
        SmoothGreedy();
        double Evaluate(Board board);
    protected:
    private:
};

#endif // SMOOTHGREEDY_H
