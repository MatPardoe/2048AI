#ifndef EVALUATION_H
#define EVALUATION_H

#include <Board.h>

class Evaluation
{
    public:
        virtual double Evaluate(Board board) = 0;
    protected:
    private:
};

#endif // EVALUATION_H
