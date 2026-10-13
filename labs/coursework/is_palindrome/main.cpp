#include <iostream>
#include "palindrome.h"

int main() {
    std::cout << std::boolalpha;
    std::cout << "Rotavator: " << is_palindrome("Rotavator") << std::endl;
    std::cout << "mom: " << is_palindrome("mom") << std::endl;
    std::cout << "Sam: " << is_palindrome("Sam") << std::endl;
    return 0;
}
