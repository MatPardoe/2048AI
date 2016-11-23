#ifndef TIDY_H
#define TIDY_H

#include <Board.h>
#include <Evaluation.h>

class Tidy : public Evaluation
{
    public:
        Tidy();
        double Evaluate(Board board);
    protected:
    private:
};

#endif // TIDY_H
