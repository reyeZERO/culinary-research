# Large Battlefield Tic-Tac-Toe


This project implements a variable-size tic-tac-toe style game supporting arbitrary width and height (each > 3) and a configurable number of marks in a row required to win. It includes two special abilities:


- Paladin shift: move one of your marks to an adjacent empty cell (8-directional adjacency).
- Alchemist swap: swap two occupied cells that contain different marks.


## Build and run


Requirements: C++17 compatible compiler and CMake.


Commands:


```bash
mkdir build
cd build
cmake ..
cmake --build .
./tictactoe
