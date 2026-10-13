#include "TicTacToe.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

TicTacToe::TicTacToe() {
    reset();
}

void TicTacToe::reset() {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '1' + (count++ - 1);
        }
    }
}

void TicTacToe::printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool TicTacToe::playerMove(char symbol) {
    int choice;
    while (true) {
        cout << "Choose a position (1-9): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (choice >= 1 && choice <= 9 && board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = symbol;
            return true;
        } else {
            cout << "Invalid move.\n";
        }
    }
}

void TicTacToe::aiMove(char symbol) {
    vector<int> emptySpots;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                emptySpots.push_back((i * 3) + j + 1);
            }
        }
    }

    if (!emptySpots.empty()) {
        int r = rand() % emptySpots.size();
        int choice = emptySpots[r];
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;
        board[row][col] = symbol;
        cout << "Opponent chose " << choice << "!\n";
    }
}

char TicTacToe::checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];

    bool full = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') full = false;
        }
    }
    if (full) return 'D';

    return ' ';
}
