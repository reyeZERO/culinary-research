#include <iostream>
#include <cassert>
#include "TicTacToe.h"
#include "Character.h"

using namespace std;

void testTicTacToe() {
    TicTacToe game;
    assert(game.checkWin() == ' ');
    cout << "TicTacToe init passed.\n";
}

void testCharacterStats() {
    Player p("TestHero", "Paladin");
    assert(p.getMaxHp() == 25);
    p.takeDamage(10);
    assert(p.getHp() < 25);
    p.heal(100);
    assert(p.getHp() == 25);
    cout << "Character logic passed.\n";
}

int main() {
    testTicTacToe();
    testCharacterStats();
    cout << "All tests passed.\n";
    return 0;
}
