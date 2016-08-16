#ifndef BOARD_H
#define BOARD_H

enum Direction {Up, Right, Down, Left};

class Board
{
    public:
        //constructors
        Board();
        Board(int currentBoard[4][4], int currentScore);
        //functions
        int GetScore();
        void Move(Direction direction);
        void MakeMove(Direction direction);
        bool CanMakeMove(Direction direction);
        bool CanMakeAMove();
        void DisplayBoard();
        void AddTile(int i, int j, int value);
        int EndGame();
    protected:
    private:
        //variables
        int board[4][4];
        int score;
        //functions
        bool CanMakeUpMove();
        bool CanMakeRightMove();
        bool CanMakeDownMove();
        bool CanMakeLeftMove();
        void MakeUpMove();
        void MakeRightMove();
        void MakeDownMove();
        void MakeLeftMove();
};

#endif // BOARD_H
