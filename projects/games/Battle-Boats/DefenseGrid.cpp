#include "DefenseGrid.h"

DefenseGrid::DefenseGrid() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            grid[i][j] = WATER;
}

bool DefenseGrid::placeBoat(int row, int col) {
    if (row < 0 || row >= 4 || col < 0 || col >= 4) return false;
    if (grid[row][col] != WATER) return false;
    grid[row][col] = BOAT;
    return true;
}

bool DefenseGrid::receiveAttack(int row, int col) {
    if (row < 0 || row >= 4 || col < 0 || col >= 4) return false;
    if (grid[row][col] == BOAT) {
        grid[row][col] = HIT;
        return true;
    } else if (grid[row][col] == WATER) {
        grid[row][col] = MISS;
    }
    return false;
}

bool DefenseGrid::isBoatSunk() const {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (grid[i][j] == BOAT) return false;
    return true;
}

DefenseGrid::CellState DefenseGrid::getCellState(int row, int col) const {
    if (row < 0 || row >= 4 || col < 0 || col >= 4) return WATER;
    return grid[row][col];
}
