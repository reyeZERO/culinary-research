#include "AttackGrid.h"

AttackGrid::AttackGrid() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            grid[i][j] = UNKNOWN;
}

void AttackGrid::markHit(int row, int col) {
    if (row >= 0 && row < 4 && col >= 0 && col < 4)
        grid[row][col] = HIT;
}

void AttackGrid::markMiss(int row, int col) {
    if (row >= 0 && row < 4 && col >= 0 && col < 4)
        grid[row][col] = MISS;
}

bool AttackGrid::isCellUnknown(int row, int col) const {
    if (row < 0 || row >= 4 || col < 0 || col >= 4) return false;
    return grid[row][col] == UNKNOWN;
}

AttackGrid::CellState AttackGrid::getCellState(int row, int col) const {
    if (row < 0 || row >= 4 || col < 0 || col >= 4) return UNKNOWN;
    return grid[row][col];
}
