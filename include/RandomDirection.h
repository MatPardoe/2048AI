#ifndef RANDOMDIRECTION_H
#define RANDOMDIRECTION_H

#include <Controler.h>
#include <Board.h>


class RandomDirection : public Controler
{
    public:
        RandomDirection();
        Direction GetMove(Board board);
    protected:
    private:
        int board[4][4];
        Direction choices[4];
};

#endif // RANDOMDIRECTION_H
