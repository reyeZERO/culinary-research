#include <iostream>
#include <string>
#include "battle_board.h"


int main() {
int w, h, k;
std::cout << "Enter battlefield width (>3): ";
if (!(std::cin >> w)) return 1;
std::cout << "Enter battlefield height (>3): ";
if (!(std::cin >> h)) return 1;
std::cout << "Enter marks in a row required to win: ";
if (!(std::cin >> k)) return 1;
if (w <= 3 || h <= 3) {
std::cout << "Width and height must be > 3\n";
return 1;
}
if (k < 3) {
std::cout << "Win requirement must be at least 3\n";
return 1;
}
if (!(k < w || k < h)) {
std::cout << "Win requirement must be less than the width or the height so victory is possible.\n";
return 1;
}
BattleBoard board(w,h,k);
char mark1 = 'X';
char mark2 = 'O';
int currentPlayer = 1;
while (true) {
board.printBoard(true);
if (board.isWin(mark1)) { std::cout << "Player 1 wins!\n"; break; }
if (board.isWin(mark2)) { std::cout << "Player 2 wins!\n"; break; }
if (board.isFull()) { std::cout << "Draw!\n"; break; }
char curMark = (currentPlayer == 1 ? mark1 : mark2);
std::cout << "Player " << currentPlayer << " (" << curMark << ") - choose action:\n";
std::cout << "1) Place mark\n";
std::cout << "2) Paladin shift (move one of your marks to an adjacent empty cell)\n";
std::cout << "3) Alchemist swap (swap two occupied cells with different marks)\n";
std::cout << "4) Quit\n";
int action;
if (!(std::cin >> action)) break;
if (action == 4) { std::cout << "Quitting.\n"; break; }
if (action == 1) {
std::cout << "Enter cell to place mark: ";
int cell;
std::cin >> cell;
if (!board.placeMark(cell, curMark)) {
std::cout << "Invalid placement. Try again.\n";
continue;
}
} else if (action == 2) {
std::cout << "Enter source cell (your mark): ";
int src;
std::cin >> src;
if (board.markAt(src) != curMark) { std::cout << "Source does not contain your mark.\n"; continue; }
std::cout << "Enter destination cell (must be adjacent and empty): ";
int dst;
std::cin >> dst;
if (!board.areAdjacent(src,dst)) { std::cout << "Cells are not adjacent.\n"; continue; }
if (!board.shiftMark(src,dst)) { std::cout << "Shift failed. Ensure destination is empty.\n"; continue; }
} else if (action == 3) {
if (board.markCount() < 2) { std::cout << "Not enough marks on board to swap.\n"; continue; }
std::cout << "Enter first cell to swap: ";
int a; std::cin >> a;
std::cout << "Enter second cell to swap: ";
int b; std::cin >> b;
if (!board.swapMarks(a,b)) { std::cout << "Swap failed. Cells must be occupied and contain different marks.\n"; continue; }
} else {
std::cout << "Unknown action.\n";
continue;
}
currentPlayer = 3 - currentPlayer;
}
return 0;
}
