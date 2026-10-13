#include <iostream>
#include <string>
#include "source_code.h"

int main() {
    std::string input_sentence;

    std::cout << "Welcome to the Cat Word Processor! Please enter a sentence:\n";
    std::getline(std::cin, input_sentence);

    std::cout << "\nYour sentence is:\n" << input_sentence << "\n";

    std::string catified_sentence = replaceWords(input_sentence);

    std::cout << "\nYour catified sentence is:\n" << catified_sentence << "\n";
    std::cout << "\nHave a cat-tastic day!\n";

    return 0;
}
