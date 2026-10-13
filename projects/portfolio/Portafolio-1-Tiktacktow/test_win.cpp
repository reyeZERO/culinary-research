#include <cassert>
#include "tic_tac_toe_lib.hpp"

int main() {
    Board b{}; b.fill(' ');
    b[0]='X'; b[1]='X'; b[2]='X';
    assert(isWin(b,'X') && !isWin(b,'O'));

    b.fill(' ');
    b[0]='O'; b[3]='O'; b[6]='O';
    assert(isWin(b,'O') && !isWin(b,'X'));

    b.fill(' ');
    b[0]='X'; b[4]='X'; b[8]='X';
    assert(isWin(b,'X'));

    b.fill(' ');
    b[2]='O'; b[4]='O'; b[6]='O';
    assert(isWin(b,'O'));

    b.fill(' ');
    b[0]='X'; b[1]='X'; b[3]='X';
    assert(!isWin(b,'X'));

    return 0;
}
