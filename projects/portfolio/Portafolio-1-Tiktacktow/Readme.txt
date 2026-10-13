

This project implements a two–player terminal Tic-Tac-Toe game in C++ along with a small test suite.


- `tic_tac_toe.cpp` — the main playable game (human vs human).
- `tic_tac_toe_lib.hpp` — helper functions (`isWin`, `isFull`, `parseIndex`) used by both the game and tests.
- `test_win.cpp` — unit tests for win detection.
- `test_full_tie.cpp` — unit tests for tie and full-board detection.
- `test_parse.cpp` — unit tests for input parsing.

run
```bash
g++ -std=c++17 -Wall -Wextra -O2 tic_tac_toe.cpp -o tic_tac_toe
./tic_tac_toe
