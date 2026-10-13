#include "Character.h"
#include "GameEngine.h"
#include "FileManager.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Player hero("Hero", "Paladin");
    bool loaded = false;

    cout << "\n=== TIC-TAC-TOE RPG ===\n";
    cout << "1. New Game\n2. Load Game\nChoice: ";
    int startChoice;
    cin >> startChoice;

    if (startChoice == 2) {
        loaded = FileManager::loadGame(hero);
    } 
    
    if (!loaded) {
        string name;
        int roleC;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Class (1: Paladin, 2: Alchemist): ";
        cin >> roleC;
        string role = (roleC == 2) ? "Alchemist" : "Paladin";
        hero = Player(name, role);
        hero.setStoryStep(1);
    }

    bool running = true;
    while (running && hero.isAlive()) {
        
        switch (hero.getStoryStep()) {
            case 1: {
                cout << "\n[Chapter 1: The Minion]\n";
                Enemy e1("Goblin", 15, 3, 0, 5, "Savage Bite");
                if (runBattle(hero, &e1)) hero.setStoryStep(2);
                else running = false;
                break;
            }
            case 2: {
                restEvent(hero);
                hero.setStoryStep(3);
                break;
            }
            case 3: {
                cout << "\n[Chapter 2: The Fork in the Road]\n";
                cout << "1. The Dark Forest\n";
                cout << "2. The Volcanic Peaks\n";
                cout << "Choice: ";
                int path; cin >> path;
                if (path == 2) hero.setStoryStep(5);
                else hero.setStoryStep(4);
                FileManager::saveGame(hero);
                break;
            }
            case 4: {
                cout << "\n[Chapter 3: The Forest Ambush]\n";
                Enemy e2("Bandit", 20, 4, 1, 10, "Smoke Bomb");
                if (runBattle(hero, &e2)) {
                     fountainEvent(hero);
                     hero.setStoryStep(6);
                } else running = false;
                break;
            }
            case 5: {
                cout << "\n[Chapter 3: The Magma Guardian]\n";
                Enemy e3("Magma Golem", 40, 7, 3, 50, "Troll Regeneration");
                if (runBattle(hero, &e3)) hero.setStoryStep(6);
                else running = false;
                break;
            }
            case 6: {
                cout << "\n[Chapter 4: The Preparation]\n";
                shopEvent(hero);
                hero.setStoryStep(7);
                break;
            }
            case 7: {
                cout << "\n[Final Chapter: The Dragon Lord]\n";
                Boss boss;
                if (runBattle(hero, &boss)) hero.setStoryStep(8);
                else running = false;
                break;
            }
            case 8: {
                cout << "\n*** YOU HAVE WON THE GAME! ***\n";
                running = false;
                break;
            }
        }
    }

    if (!hero.isAlive()) {
        cout << "Game Over. Restart to try again.\n";
    }

    return 0;
}
