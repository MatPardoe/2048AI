#ifndef CONTROLER_H
#define CONTROLER_H

#include <Board.h>

class Controler
{
    public:
        Controler();
        virtual Direction GetMove(Board board) = 0;
    protected:
    private:
};

#endif // CONTROLER_H
