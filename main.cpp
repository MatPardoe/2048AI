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
    cout << "Hello world!" << endl;
    return 0;
}
