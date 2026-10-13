#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>

using namespace std;

class Character {
protected:
    string name;
    string role;
    int maxHp;
    int hp;
    int attack;
    int defense;
    int gold;
    int storyStep;

public:
    Character(string n, int h, int a, int d, int g);
    virtual ~Character();

    bool isAlive() const;
    string getName() const;
    string getRole() const;
    int getHp() const;
    int getMaxHp() const;
    int getAttack() const;
    int getDefense() const;
    int getGold() const;
    int getStoryStep() const;

    void setStats(int curHp, int mHp, int atk, int def, int g, int step);
    void setStoryStep(int step);

    void takeDamage(int dmg);
    void heal(int amount);
    void addGold(int amount);
    bool spendGold(int amount);
    void upgradeAttack(int amt);
    void upgradeDefense(int amt);

    virtual void triggerAbility(Character* opponent);
};

class Player : public Character {
public:
    Player(string n, string r);
};

class Enemy : public Character {
    string abilityName;
public:
    Enemy(string n, int h, int a, int d, int g, string abName);
    void triggerAbility(Character* opponent) override;
};

class Boss : public Enemy {
public:
    Boss();
    void triggerAbility(Character* opponent) override;
};

#endif
