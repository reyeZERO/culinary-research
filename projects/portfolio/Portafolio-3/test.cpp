#include "game.h"
#include <cassert>
#include <iostream>

void testBasicSurvival() {
    Rules rules;
    rules.inputRules = []() {};
    assert(rules.shouldBirth(3) == false);
    assert(rules.shouldSurvive(2) == false);
    std::cout << "Placeholder test passed. Replace with real test cases.\n";
}

int main() {
    testBasicSurvival();
    return 0;
}
