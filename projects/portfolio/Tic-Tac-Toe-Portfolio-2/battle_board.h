#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


class BattleBoard {
public:
BattleBoard(int width, int height, int win_k);
bool cellToRC(int cell, int &r, int &c) const;
int rcToCell(int r, int c) const;
bool placeMark(int cell, char mark);
bool removeMark(int cell);
bool swapMarks(int cellA, int cellB);
bool shiftMark(int srcCell, int destCell);
bool isWin(char mark) const;
bool isFull() const;
int markCount() const;
bool areAdjacent(int srcCell, int destCell) const;
void printBoard(bool showNumbers = false) const;
int getWidth() const;
int getHeight() const;
int getWinK() const;
char markAt(int cell) const;
private:
int width, height, win_k;
std::vector<char> grid;
bool inBounds(int r, int c) const;
};
