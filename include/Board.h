#ifndef BOARD_H
#define BOARD_H

enum Direction {Up, Right, Down, Left};

class Board
{
    public:
        Board();
        Board(int currentBoard[4][4], int currentScore);
        int GetScore();
        void MakeMove(Direction direction);
        bool CanMakeMove(Direction direction);
        bool CanMakeAMove();
        void DisplayBoard();
        void AddTile();
        int EndGame();
    protected:
    private:
        int board[4][4];
        int score;
        bool CanMakeUpMove();
        bool CanMakeRightMove();
        bool CanMakeDownMove();
        bool CanMakeLeftMove();
};

#endif // BOARD_H
