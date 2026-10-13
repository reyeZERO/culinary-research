#include "Character.h"
#include <algorithm>
#include <cstdlib>

Character::Character(string n, int h, int a, int d, int g) 
    : name(n), maxHp(h), hp(h), attack(a), defense(d), gold(g), role("NPC"), storyStep(0) {}

Character::~Character() {}

bool Character::isAlive() const { return hp > 0; }
string Character::getName() const { return name; }
string Character::getRole() const { return role; }
int Character::getHp() const { return hp; }
int Character::getMaxHp() const { return maxHp; }
int Character::getAttack() const { return attack; }
int Character::getDefense() const { return defense; }
int Character::getGold() const { return gold; }
int Character::getStoryStep() const { return storyStep; }

void Character::setStats(int curHp, int mHp, int atk, int def, int g, int step) {
    hp = curHp; maxHp = mHp; attack = atk; defense = def; gold = g; storyStep = step;
}

void Character::setStoryStep(int step) { storyStep = step; }

void Character::takeDamage(int dmg) {
    int actualDmg = max(1, dmg - defense);
    hp -= actualDmg;
    cout << name << " takes " << actualDmg << " damage!\n";
}

void Character::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
    cout << name << " heals " << amount << " HP.\n";
}

void Character::addGold(int amount) { gold += amount; }

bool Character::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

void Character::upgradeAttack(int amt) { attack += amt; }
void Character::upgradeDefense(int amt) { defense += amt; }
void Character::triggerAbility(Character* opponent) {}

Player::Player(string n, string r) : Character(n, 0, 0, 0, 0) {
    role = r;
    if (role == "Paladin") {
        maxHp = 25; hp = 25; attack = 5; defense = 3; gold = 10;
    } else {
        maxHp = 20; hp = 20; attack = 7; defense = 1; gold = 10;
    }
}

Enemy::Enemy(string n, int h, int a, int d, int g, string abName) 
    : Character(n, h, a, d, g), abilityName(abName) {}

void Enemy::triggerAbility(Character* opponent) {
    if (rand() % 4 == 0) {
        cout << "*** " << name << " uses " << abilityName << "! ***\n";
        if (abilityName == "Savage Bite") {
            opponent->takeDamage(attack + 2);
        } else if (abilityName == "Troll Regeneration") {
            heal(3);
        } else if (abilityName == "Smoke Bomb") {
            defense += 2; 
        }
    }
}

Boss::Boss() : Enemy("Dragon Lord", 40, 9, 4, 100, "Multi") {}

void Boss::triggerAbility(Character* opponent) {
    if (rand() % 3 == 0) {
        int which = rand() % 2;
        if (which == 0) {
            cout << "*** DRAGON BREATHES FIRE! ***\n";
            opponent->takeDamage(8);
        } else {
            cout << "*** DRAGON ROARS! ***\n";
            heal(5);
        }
    }
}
