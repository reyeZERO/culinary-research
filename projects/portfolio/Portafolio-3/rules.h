#ifndef RULES_H
#define RULES_H

#include <set>

class Rules {
public:
    void inputRules();
    bool shouldBirth(int neighbors);
    bool shouldSurvive(int neighbors);

private:
    std::set<int> birth;
    std::set<int> survive;
};

#endif
