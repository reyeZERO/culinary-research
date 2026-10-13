#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Character.h"

void printStatsLine(const Player& p, const Character& e);
bool runBattle(Player& p, Character* e);
void shopEvent(Player& p);
void restEvent(Player& p);
void fountainEvent(Player& p);

#endif
