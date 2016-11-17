#ifndef POSITIONAL_H
#define POSITIONAL_H

#include <Board.h>
#include <Evaluation.h>


class Positional : public Evaluation
{
    public:
        Positional();
        double Evaluate(Board board);
    protected:
    private:
};

#endif // POSITIONAL_H
