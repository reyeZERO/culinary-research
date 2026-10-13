#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Character.h"
#include <fstream>

class FileManager {
public:
    static void saveGame(const Player& p);
    static bool loadGame(Player& p);
};

#endif
