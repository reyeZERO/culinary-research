#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "DefenseGrid.h"
#include "AttackGrid.h"

using namespace std;

string getDefenseCellSymbol(DefenseGrid::CellState state, char boatSymbol) {
    switch (state) {
        case DefenseGrid::WATER: return "_";
        case DefenseGrid::BOAT: return string(1, boatSymbol);
        case DefenseGrid::HIT: return "💥";
        case DefenseGrid::MISS: return "❌";
        default: return "?";
    }
}

string getAttackCellSymbol(AttackGrid::CellState state) {
    switch (state) {
        case AttackGrid::UNKNOWN: return "_";
        case AttackGrid::HIT: return "💥";
        case AttackGrid::MISS: return "❌";
        default: return "?";
    }
}

void displayGrids(const DefenseGrid& playerDefense, const AttackGrid& playerAttack, char boatSymbol) {
    cout << "You:                Computer:\n\n";
    cout << "   1 2 3 4          1 2 3 4\n";
    for (int row = 0; row < 4; ++row) {
        char label = 'A' + row;
        cout << label << " ";
        for (int col = 0; col < 4; ++col)
            cout << getDefenseCellSymbol(playerDefense.getCellState(row, col), boatSymbol) << " ";
        cout << "     " << label << " ";
        for (int col = 0; col < 4; ++col)
            cout << getAttackCellSymbol(playerAttack.getCellState(row, col)) << " ";
        cout << endl;
    }
}

void playGame() {
    DefenseGrid playerDefense, computerDefense;
    AttackGrid playerAttack, computerAttack;
    char boatSymbol = '⛵';
    string input;

    cout << "Welcome to Battle Boats!\n\n";
    displayGrids(playerDefense, playerAttack, boatSymbol);
    cout << "\nWhere would you like to hide your boat?\n\n";

    bool valid = false;
    while (!valid) {
        getline(cin, input);
        if (input.size() < 2) {
            cout << "Invalid input. Try again.\n";
            continue;
        }
        char rowChar = toupper(input[0]);
        int row = rowChar - 'A';
        int col;
        try { col = stoi(input.substr(1)) - 1; }
        catch (...) {
            cout << "Invalid column. Try again.\n";
            continue;
        }
        if (row < 0 || row >= 4 || col < 0 || col >= 4) {
            cout << "Invalid position. Try again.\n";
            continue;
        }
        valid = playerDefense.placeBoat(row, col);
        if (!valid) cout << "Invalid position. Try again.\n";
    }

    cout << "Enter a character to represent your boat (default ⛵): ";
    getline(cin, input);
    if (!input.empty()) boatSymbol = input[0];

    int compRow, compCol;
    do {
        compRow = rand() % 4;
        compCol = rand() % 4;
    } while (!computerDefense.placeBoat(compRow, compCol));

    bool gameOver = false;
    while (!gameOver) {
        displayGrids(playerDefense, playerAttack, boatSymbol);
        cout << "\nPick a spot: ";
        valid = false;
        int attackRow, attackCol;
        while (!valid) {
            getline(cin, input);
            if (input.size() < 2) {
                cout << "Invalid input. Try again.\n";
                continue;
            }
            char rowChar = toupper(input[0]);
            attackRow = rowChar - 'A';
            try { attackCol = stoi(input.substr(1)) - 1; }
            catch (...) {
                cout << "Invalid column. Try again.\n";
                continue;
            }
            if (attackRow < 0 || attackRow >= 4 || attackCol < 0 || attackCol >= 4) {
                cout << "Invalid position. Try again.\n";
                continue;
            }
            if (!playerAttack.isCellUnknown(attackRow, attackCol)) {
                cout << "Already attacked. Try again.\n";
                continue;
            }
            valid = true;
        }

        bool hit = computerDefense.receiveAttack(attackRow, attackCol);
        hit ? playerAttack.markHit(attackRow, attackCol) : playerAttack.markMiss(attackRow, attackCol);
        cout << "You chose " << input << ". You " << (hit ? "hit!" : "missed!") << endl;

        if (computerDefense.isBoatSunk()) {
            displayGrids(playerDefense, playerAttack, boatSymbol);
            cout << "\nYou win the game! Great job!\n";
            gameOver = true;
            continue;
        }

        int compAttackRow, compAttackCol;
        do {
            compAttackRow = rand() % 4;
            compAttackCol = rand() % 4;
        } while (!computerAttack.isCellUnknown(compAttackRow, compAttackCol));

        bool compHit = playerDefense.receiveAttack(compAttackRow, compAttackCol);
        compHit ? computerAttack.markHit(compAttackRow, compAttackCol) : computerAttack.markMiss(compAttackRow, compAttackCol);
        cout << "Computer chose " << char('A' + compAttackRow) << compAttackCol + 1 << ". They " << (compHit ? "hit!" : "missed!") << endl;

        if (playerDefense.isBoatSunk()) {
            displayGrids(playerDefense, playerAttack, boatSymbol);
            cout << "\nComputer wins! Better luck next time!\n";
            gameOver = true;
        }
    }
}

int main() {
    srand(time(0));
    string input;
    do {
        playGame();
        cout << "Play again? (Y/N): ";
        getline(cin, input);
    } while (toupper(input[0]) == 'Y');
    return 0;
}
