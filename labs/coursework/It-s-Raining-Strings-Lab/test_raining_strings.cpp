#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    {
        std::ofstream input("input.txt");
        input << "WalMart\n"
              << "y\n"
              << "JC Penney\n"
              << "Y\n"
              << "Merlin Muffler\n"
              << "yes\n"
              << "Appleby's\n"
              << "Yes\n"
              << "Zippy's\n"
              << "no\n";
    }

    std::system("./raining_strings < input.txt > output.txt");

    std::ifstream out("output.txt");
    std::stringstream buffer;
    buffer << out.rdbuf();
    std::string output = buffer.str();

    assert(output.find("WalMart") != std::string::npos);
    assert(output.find("JC Penney") != std::string::npos);
    assert(output.find("Merlin Muffler") != std::string::npos);
    assert(output.find("Appleby's") != std::string::npos);
    assert(output.find("Zippy's") != std::string::npos);
    assert(output.find("Thank you for using the Business Sorting Program!") != std::string::npos);

    std::cout << "OK\n";
}
