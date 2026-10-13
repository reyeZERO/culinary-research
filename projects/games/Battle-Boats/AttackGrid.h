#ifndef ATTACKGRID_H
#define ATTACKGRID_H

class AttackGrid {
public:
    enum CellState { UNKNOWN, HIT, MISS };
    AttackGrid();
    void markHit(int row, int col);
    void markMiss(int row, int col);
    bool isCellUnknown(int row, int col) const;
    CellState getCellState(int row, int col) const;

private:
    CellState grid[4][4];
};

#endif
