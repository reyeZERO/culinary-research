#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe {
private:
    char board[3][3];

public:
    TicTacToe();
    void reset();
    void printBoard();
    bool playerMove(char symbol);
    void aiMove(char symbol);
    char checkWin();
};

#endif
