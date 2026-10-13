#include "FileManager.h"
#include <iostream>

void FileManager::saveGame(const Player& p) {
    ofstream file("savegame.txt");
    if (file.is_open()) {
        file << p.getName() << "\n" 
             << p.getRole() << "\n"
             << p.getHp() << "\n" 
             << p.getMaxHp() << "\n" 
             << p.getAttack() << "\n" 
             << p.getDefense() << "\n" 
             << p.getGold() << "\n" 
             << p.getStoryStep();
        file.close();
        cout << "[Game Saved]\n";
    } else {
        cout << "[Error Saving Game]\n";
    }
}

bool FileManager::loadGame(Player& p) {
    ifstream file("savegame.txt");
    if (file.is_open()) {
        string name, role;
        int hp, mhp, atk, def, gold, step;
        
        if (file >> name >> role >> hp >> mhp >> atk >> def >> gold >> step) {
            p = Player(name, role); 
            p.setStats(hp, mhp, atk, def, gold, step);
            file.close();
            cout << "[Game Loaded Successfully!]\n";
            return true;
        }
    }
    cout << "[No Save File Found]\n";
    return false;
}
