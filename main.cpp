#include <iostream>
#include <cstdlib>
#include <time.h> //seeds the random number generator

#include <Board.h>
#include <Controler.h>
#include <RandomDirection.h>
#include <ControlerFactory.h>

using namespace std;


int main()
{
    Board board;
    ControlerFactory factory;
    Controler* controler = factory.GetControler();
    board.DisplayBoard();
    cout << "Hello world!" << endl;

    RandomDirection randomDirection;
    while (board.CanMakeAMove())
    {
        board.Move(randomDirection.GetMove(board));
    }
    board.DisplayBoard();
    cout << board.GetScore() << endl;

    /*
    // testing code
    // 1
    board.AddTile(0,0,2);
    board.AddTile(0,1,2);
    board.AddTile(0,2,2);
    board.AddTile(0,3,2);
    // 2
    board.AddTile(1,0,2);
    board.AddTile(1,1,2);
    board.AddTile(1,2,2);
    board.AddTile(1,3,2);
    // 3
    board.AddTile(2,0,2);
    board.AddTile(2,1,2);
    board.AddTile(2,2,2);
    board.AddTile(2,3,2);
    // 4
    board.AddTile(3,0,2);
    board.AddTile(3,1,2);
    board.AddTile(3,2,2);
    board.AddTile(3,3,2);
    // testing
    board.DisplayBoard();
    board.MakeMove(Down);
    cout << "Results Board : " << endl;
    board.DisplayBoard();
    board.MakeMove(Right);
    cout << "Board : " << endl;
    board.DisplayBoard();
    board.MakeMove(Left);
    cout << "Board : " << endl;
    board.DisplayBoard();
    board.MakeMove(Up);
    cout << "Another Board : " << endl;
    board.DisplayBoard();
    // testing code end
    */
    return 0;
}
