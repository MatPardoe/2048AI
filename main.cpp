#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <fstream>

#include <Board.h>
#include <Controler.h>
//#include <RandomDirection.h>
//#include <MinMax.h>
#include <ControlerFactory.h>

using namespace std;


int main(int argc, char *argv[])
{
    //setup all variables
    string outputName;
    int games;
    int choice;
    int treeDepth;
    int evaluation;
    ControlerFactory factory;

    if( argc == 6)
    {
        //this has no error handling and just assumes that you have done it correctly
        outputName = argv[1];
        games = atoi(argv[2]);
        choice = atoi(argv[3]);
        treeDepth = atoi(argv[4]);
        evaluation = atoi(argv[5]);
    }
    else
    {
        // get initial input from person running the code for csv name number of games
        cout << "What do you want to call the output csv file ? ";
        cin >> outputName;
        outputName = outputName + ".csv";
        cout << "How many games do you want to run ? ";
        cin >> games;

        // get the AI that is going to be used this run and all related information (tree depth and heuristic)
        factory.DisplayOptions();
        cout << "Which algorithm do you want to use ? ";
        cin >> choice;
        cout << "If your chosen algorithm creates a tree (if it doesn't it doesn't matter what you choose) how deep do you want it to go (the deeper you go the longer it takes) ? ";
        cin >> treeDepth;
        factory.DisplayEvaluationOptions();
        cout << "which evaluation function do you want to use ? ";
        cin >> evaluation;
    }

    // set up arrays for all of the values you want to be able to output
    int scores[games];
    int moves[games];
    clock_t time[games];
    int maximum[games];

    // create the controler
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
