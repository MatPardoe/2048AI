#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <fstream>
#include <utility>

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
    int display;
    int learning;
    string stateName;
    int hard;
    ControlerFactory factory;

    //seed the random number generator
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);

    if(argc == 10)
    {
        //this has no error handling and just assumes that you have done it correctly
        outputName = argv[1];
        games = atoi(argv[2]);
        choice = atoi(argv[3]);
        treeDepth = atoi(argv[4]);
        evaluation = atoi(argv[5]);
        display = atoi(argv[6]);
        learning = atoi(argv[7]);
        stateName = argv[8];
        hard = atoi(argv[9]);
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
        cout << "If your chosen algorithm creates a tree how deep do you want it to go (the deeper you go the longer it takes)? ";
        cin >> treeDepth;
        factory.DisplayEvaluationOptions();
        cout << "which evaluation function do you want to use ? ";
        cin >> evaluation;
        cout << "1 to display boards, any other value not to ";
        cin >> display;
        cout << "How many games do you want to play while learning? ";
        cin >> learning;
        cout << "If you are learning a model what do you want to save the model as/ what is the name of the model? ";
        cin >> stateName;
        cout << "If you want to start in a challenging position select 1 ";
        cin >> hard;
    }

    // set up arrays for all of the values you want to be able to output
    int scores[games];
    int moves[games];
    int movesAt2048[games];
    int scoresAt2048[games];
    clock_t time[games];
    int maximum[games];

    // create the controler
    Controler* controler = factory.GetControler(choice,treeDepth,evaluation,learning,stateName);

    // run all the required games
    for (int i = 0; i < games; i++)
    {
        Board board;
        if(hard == 1)
        {
            //creating hard start position
            board.AddTile(0,0,2);
            board.AddTile(0,1,4);
            board.AddTile(0,2,2);
            board.AddTile(0,3,4);

            board.AddTile(1,0,4);
            board.AddTile(1,1,2);
            board.AddTile(1,2,4);
            board.AddTile(1,3,2);

            board.AddTile(2,0,2);
            board.AddTile(2,1,4);
            board.AddTile(2,2,2);
            board.AddTile(2,3,4);
            //done creating hard start position
        }

        time[i] = clock(); //start timer
        while (board.CanMakeAMove())
        {
            board.Move((*controler).GetMove(board)); // passing the board is automatically copied instead of sharing the object
            if(display==1)
            {
                board.DisplayBoard();
            }
        }
        time[i] = clock()-time[i]; //get overall time for the game
        scores[i] = board.GetScore();

        std::pair<int, std::pair<int, int> > tempPairPair = board.EndGame();
        moves[i] = tempPairPair.first;
        scoresAt2048[i] = tempPairPair.second.first;
        movesAt2048[i] = tempPairPair.second.second;


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

        //board.DisplayBoard();
    }

    //write output
    ofstream outFile (outputName.c_str());
    if (outFile.is_open())
    {
        // header line
        outFile << "score, moves, time (seconds), highest value, score at 2048 tile, moves at 2048 tile\n";
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

            // getting the score at 2048
            convert << scoresAt2048[i];
            line = line + convert.str() + ", ";
            convert.str("");

            // getting the moves at 2048
            convert << movesAt2048[i];
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
