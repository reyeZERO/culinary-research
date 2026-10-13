#include "GameEngine.h"
#include "TicTacToe.h"
#include "FileManager.h"
#include <iostream>

using namespace std;

void printStatsLine(const Player& p, const Character& e) {
    cout << "\n-------------------------------------------------\n";
    cout << p.getName() << " [HP: " << p.getHp() << " | Atk: " << p.getAttack() << "]";
    cout << " VS ";
    cout << e.getName() << " [HP: " << e.getHp() << " | Atk: " << e.getAttack() << "]";
    cout << "\n-------------------------------------------------\n";
}

bool runBattle(Player& p, Character* e) {
    TicTacToe game;
    cout << "\n--- BATTLE: " << e->getName() << " ---\n";
    
    while (p.isAlive() && e->isAlive()) {
        printStatsLine(p, *e);
        game.reset();
        char winner = ' ';
        bool playerTurn = true;

        while (winner == ' ') {
            game.printBoard();
            if (playerTurn) {
                cout << "Your turn (X). 0 to Save & Quit: ";
                int in;
                if (!(cin >> in)) {
                    cin.clear(); cin.ignore(1000, '\n');
                    continue;
                }
                if (in == 0) {
                    FileManager::saveGame(p);
                    exit(0); 
                }
            }
            if (playerTurn) game.playerMove('X');
            else game.aiMove('O');
            
            winner = game.checkWin();
            playerTurn = !playerTurn;
        }

        game.printBoard();
        if (winner == 'X') {
            cout << "You win match!\n";
            e->takeDamage(p.getAttack());
        } else if (winner == 'O') {
            cout << "Enemy wins match!\n";
            p.takeDamage(e->getAttack());
        } else {
            cout << "Draw! 1 damage each.\n";
            p.takeDamage(p.getDefense() + 1);
            e->takeDamage(e->getDefense() + 1);
        }

        if (e->isAlive()) {
            e->triggerAbility(&p);
        }
    }

    if (p.isAlive()) {
        cout << "\nVICTORY!\n";
        p.addGold(e->getGold());
        return true;
    } else {
        cout << "\nDEFEAT...\n";
        return false;
    }
}

void shopEvent(Player& p) {
    cout << "\n--- MERCHANT ---\n";
    while (true) {
        cout << "Gold: " << p.getGold() << "\n";
        cout << "1. Potion (5g)\n2. Sharpen (15g)\n3. Armor (15g)\n4. Leave/Save\nChoice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            if (p.spendGold(5)) p.heal(10);
            else cout << "Need gold.\n";
        } else if (choice == 2) {
            if (p.spendGold(15)) p.upgradeAttack(1);
            else cout << "Need gold.\n";
        } else if (choice == 3) {
            if (p.spendGold(15)) p.upgradeDefense(1);
            else cout << "Need gold.\n";
        } else if (choice == 4) {
            FileManager::saveGame(p);
            break;
        } else {
            cout << "Invalid.\n";
        }
    }
}

void restEvent(Player& p) {
    cout << "\n--- CAMPFIRE ---\n";
    cout << "1. Sleep (Heal)\n2. Train (+Atk)\nChoice: ";
    int choice;
    cin >> choice;
    if (choice == 2) {
        p.upgradeAttack(1);
        cout << "Strength up!\n";
    } else {
        p.heal(10);
        cout << "Rested.\n";
    }
    FileManager::saveGame(p);
}

void fountainEvent(Player& p) {
    cout << "\n--- MYSTIC FOUNTAIN ---\n";
    cout << "1. Drink (Heal)\n2. Coin (+Def)\nChoice: ";
    int ch;
    cin >> ch;
    if (ch == 2) {
        p.upgradeDefense(1);
        cout << "Defense Up!\n";
    } else {
        p.heal(100);
        cout << "Fully Healed!\n";
    }
    FileManager::saveGame(p);
}
