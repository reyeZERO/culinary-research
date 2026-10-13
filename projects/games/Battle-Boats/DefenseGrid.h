#ifndef DEFENSEGRID_H
#define DEFENSEGRID_H

class DefenseGrid {
public:
    enum CellState { WATER, BOAT, HIT, MISS };
    DefenseGrid();
    bool placeBoat(int row, int col);
    bool receiveAttack(int row, int col);
    bool isBoatSunk() const;
    CellState getCellState(int row, int col) const;

private:
    CellState grid[4][4];
};

#endif
