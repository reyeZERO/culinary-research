#include "rules.h"
#include <iostream>

void Rules::inputRules() {
    int n;
    std::cout << "Enter neighbor counts to BIRTH a new cell (-1 to end): ";
    while (std::cin >> n && n != -1) birth.insert(n);
    std::cin.clear(); std::cin.ignore();

    std::cout << "Enter neighbor counts to KEEP a cell alive (-1 to end): ";
    while (std::cin >> n && n != -1) survive.insert(n);
    std::cin.clear(); std::cin.ignore();
}

bool Rules::shouldBirth(int neighbors) {
    return birth.count(neighbors);
}

bool Rules::shouldSurvive(int neighbors) {
    return survive.count(neighbors);
}
