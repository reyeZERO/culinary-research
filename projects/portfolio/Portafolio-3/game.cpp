#include "game.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

GameOfLife::GameOfLife() : rows(20), cols(40), generation(0), isRunning(true) {
    grid.resize(rows, std::vector<bool>(cols, false));
    nextGrid = grid;
}

void GameOfLife::configureRules() {
    rules.inputRules();
}

void GameOfLife::initialize() {
    std::cout << "Enter initial live cells (row col), type -1 -1 to stop:\n";
    int r, c;
    while (true) {
        std::cin >> r >> c;
        if (r == -1 || c == -1) break;
        if (r >= 0 && r < rows && c >= 0 && c < cols)
            grid[r][c] = true;
    }
}

bool GameOfLife::run() {
    std::cout << "Press ENTER to continue to next generation, or 'q' then ENTER to quit: ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty() && input[0] == 'q') return false;
    return true;
}

void GameOfLife::update() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int neighbors = countNeighbors(r, c);
            if (grid[r][c])
                nextGrid[r][c] = rules.shouldSurvive(neighbors);
            else
                nextGrid[r][c] = rules.shouldBirth(neighbors);
        }
    }
    grid = nextGrid;
    generation++;
}

void GameOfLife::display() {
    clearScreen();
    std::cout << "Generation: " << generation << "\n";
    for (const auto& row : grid) {
        for (bool cell : row) {
            std::cout << (cell ? "#" : ".");
        }
        std::cout << "\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

int GameOfLife::countNeighbors(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny])
                count++;
        }
    }
    return count;
}

void GameOfLife::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}
