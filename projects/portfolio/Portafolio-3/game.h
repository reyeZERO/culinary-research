#ifndef GAME_H
#define GAME_H

#include <vector>
#include "rules.h"

class GameOfLife {
public:
    GameOfLife();
    void configureRules();
    void initialize();
    bool run();
    void update();
    void display();

private:
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> nextGrid;
    Rules rules;
    int rows;
    int cols;
    int generation;
    bool isRunning;

    int countNeighbors(int x, int y);
    void clearScreen();
};

#endif

