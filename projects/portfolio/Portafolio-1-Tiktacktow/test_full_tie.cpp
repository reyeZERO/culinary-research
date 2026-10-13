#include <cassert>
#include "tic_tac_toe_lib.hpp"

int main() {
    Board b{};
    b[0]='X'; b[1]='O'; b[2]='X';
    b[3]='X'; b[4]='O'; b[5]='O';
    b[6]='O'; b[7]='X'; b[8]='X';
    assert(isFull(b));
    assert(!isWin(b,'X'));
    assert(!isWin(b,'O'));

    Board c{}; c.fill(' ');
    assert(!isFull(c));

    c[0]='X'; c[1]='O'; c[2]='X';
    c[3]='O'; c[4]='X'; c[5]='O';
    c[6]='X'; c[7]=' '; c[8]='O';
    assert(!isFull(c));
    return 0;
}
