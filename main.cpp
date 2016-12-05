#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <fstream>

#include <Board.h>
#include <Controler.h>
#include <RandomDirection.h>
#include <MinMax.h>
#include <ControlerFactory.h>

using namespace std;


int main()
{
    // get initial input from person running the code for csv name number of games
    string outputName;
    cout << "What do you want to call the output csv file ? ";
    cin >> outputName;
    outputName = outputName + ".csv";
    int games;
    cout << "How many games do you want to run ? ";
    cin >> games;

    // set up arrays for all of the values you want to be able to output
    int scores[games];
    int moves[games];
    clock_t time[games];
    int maximum[games];

    // get the AI that is going to be used this run and all related information (tree depth and heuristic)
    ControlerFactory factory;
    factory.DisplayOptions();
    cout << "Which algorithm do you want to use ? ";
    int choice;
    cin >> choice;
    cout << "If your chosen algorithm creates a tree (if it doesn't it doesn't matter what you choose) how deep do you want it to go (the deeper you go the longer it takes) ? ";
    int treeDepth;
    cin >> treeDepth;
    factory.DisplayEvaluationOptions();
    cout << "which evaluation function do you want to use ? ";
    int evaluation;
    cin >> evaluation;

    Controler* controler = factory.GetControler(choice,treeDepth,evaluation);

    // run all the required games
    for (int i = 0; i < games; i++)
    {
        Board board;
        time[i] = clock(); //start timer
        while (board.CanMakeAMove())
        {
            board.Move((*controler).GetMove(board)); // passing the board is automatically copied instead of sharing the object
        }
        time[i] = clock()-time[i]; //get overall time for the game
        scores[i] = board.GetScore();
        moves[i] = board.EndGame();

        maximum[i] = 0;
        // find the maximum tile
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int temp = board.GetBoard(j,k);
                if (temp > maximum[i])
                {
                    maximum[i] = temp;
                }
            }
        }

        board.DisplayBoard();
    }

    //write output
    ofstream outFile (outputName.c_str());
    if (outFile.is_open())
    {
        // header line
        outFile << "score, moves, time (seconds), highest value, score at 2048 tile (not yet implemented)\n";
        for (int i = 0; i < games; i++)
        {
            string line = "";
            //can't put in numbers directly
            ostringstream convert;

            // getting the score
            convert << scores[i];
            line = convert.str() + ", ";
            convert.str("");

            // getting the moves
            convert << moves[i];
            line = line + convert.str() + ", ";
            convert.str("");

            // getting the time
            convert << (((float)time[i])/CLOCKS_PER_SEC);
            line = line + convert.str() + ", ";
            convert.str("");

            // getting the highest value tile
            convert << maximum[i];
            line = line + convert.str() + ", ";
            convert.str("");

            // placing the line in the file
            line = line + "\n";
            outFile << line;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to save the data to a file" << endl;
    }
    return 0;
}
