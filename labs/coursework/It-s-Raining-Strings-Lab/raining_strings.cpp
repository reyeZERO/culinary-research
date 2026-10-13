#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool again(const std::string& input) {
    return input == "y" || input == "Y" || input == "yes" || input == "Yes";
}

int main() {
    std::vector<std::string> businesses;
    std::string name, cont;

    std::cout << "Welcome to the Business Sorting Program!\n\n";

    while (true) {
        std::cout << "Please enter the name of a business:  ";
        std::getline(std::cin, name);
        if (name.empty()) continue;
        businesses.push_back(name);
        std::sort(businesses.begin(), businesses.end());

        if (businesses.size() == 1) {
            std::cout << "\nYour business is:\n\n";
        } else {
            std::cout << "\nYour businesses are:\n\n";
        }

        for (auto& b : businesses) {
            std::cout << "    " << b << "\n";
        }

        std::cout << "\nAnother business?  ";
        std::getline(std::cin, cont);
        if (!again(cont)) break;
    }

    std::cout << "\nThank you for using the Business Sorting Program!\n";
    return 0;
}
