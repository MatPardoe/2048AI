#include <iostream>
#include <cstdlib>
#include <time.h> //seeds the random number generator
#include <sstream>
#include <fstream>

#include <Board.h>
#include <Controler.h>
#include <RandomDirection.h>
#include <ControlerFactory.h>

using namespace std;


int main()
{
    string outputName;
    cout << "What do you want to call the output csv file ? ";
    cin >> outputName;
    outputName = outputName + ".csv";
    int games;
    cout << "How many games do you want to run ? ";
    cin >> games;
    int scores[games];
    int moves[games];
    clock_t time[games];

    RandomDirection randomDirection;
    for (int i = 0; i < games; i++)
    {
        Board board;
        time[i] = clock();
        while (board.CanMakeAMove())
        {
            board.Move(randomDirection.GetMove(board));
        }
        time[i] = clock()-time[i];
        scores[i] = board.GetScore();
        moves[i] = board.EndGame();
        board.DisplayBoard();
    }

    //write output
    ofstream outFile (outputName.c_str());
    if (outFile.is_open())
    {
        outFile << "score, moves \n";
        for (int i = 0; i < games; i++)
        {
            string line = "";
            //can't put in numbers directly
            ostringstream convert;
            convert << scores[i];
            line = convert.str() + ", ";
            convert.str("");
            convert << moves[i];
            line = line + convert.str() + "\n";
            outFile << line;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to save the data to a file" << endl;
    }


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
