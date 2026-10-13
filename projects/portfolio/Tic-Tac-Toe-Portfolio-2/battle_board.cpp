#include "battle_board.h"


BattleBoard::BattleBoard(int width, int height, int win_k)
: width(width), height(height), win_k(win_k), grid(width * height, '.') {}


bool BattleBoard::cellToRC(int cell, int &r, int &c) const {
if (cell < 1 || cell > width * height) return false;
int idx = cell - 1;
r = idx / width;
c = idx % width;
return true;
}


int BattleBoard::rcToCell(int r, int c) const {
return r * width + c + 1;
}


bool BattleBoard::placeMark(int cell, char mark) {
int r,c;
if (!cellToRC(cell, r, c)) return false;
int idx = r * width + c;
if (grid[idx] != '.') return false;
grid[idx] = mark;
return true;
}


bool BattleBoard::removeMark(int cell) {
int r,c;
if (!cellToRC(cell, r, c)) return false;
int idx = r * width + c;
grid[idx] = '.';
return true;
}


bool BattleBoard::swapMarks(int cellA, int cellB) {
if (cellA == cellB) return false;
int ra, ca, rb, cb;
if (!cellToRC(cellA, ra, ca) || !cellToRC(cellB, rb, cb)) return false;
int ia = ra * width + ca;
int ib = rb * width + cb;
if (grid[ia] == '.' || grid[ib] == '.') return false;
if (grid[ia] == grid[ib]) return false;
std::swap(grid[ia], grid[ib]);
return true;
}


bool BattleBoard::shiftMark(int srcCell, int destCell) {
if (srcCell == destCell) return false;
int rs, cs, rd, cd;
if (!cellToRC(srcCell, rs, cs) || !cellToRC(destCell, rd, cd)) return false;
int isrc = rs * width + cs;
int idst = rd * width + cd;
if (grid[isrc] == '.') return false;
if (grid[idst] != '.') return false;
int dr = std::abs(rs - rd), dc = std::abs(cs - cd);
if (std::max(dr, dc) != 1) return false;
grid[idst] = grid[isrc];
grid[isrc] = '.';
return true;
}


bool BattleBoard::isWin(char mark) const {
if (mark == '.') return false;
const int dirs[4][2] = {{0,1},{1,0},{1,1},{1,-1}};
for (int r = 0; r < height; ++r) {
for (int c = 0; c < width; ++c) {
if (grid[r * width + c] != mark) continue;
for (auto &d : dirs) {
int dr = d[0], dc = d[1];
int count = 1;
int rr = r + dr, cc = c + dc;
while (inBounds(rr, cc) && grid[rr * width + cc] == mark) {
++count;
rr += dr; cc += dc;
}
rr = r - dr; cc = c - dc;
while (inBounds(rr, cc) && grid[rr * width + cc] == mark) {
++count;
rr -= dr; cc -= dc;
}
return (r >= 0 && r < height && c >= 0 && c < width);
