#include "source_code.h"
#include <iostream>
#include <cassert>

void test_replaceWords() {
    std::string input1 = "My cat is pretty angry with me right now.";
    std::string expected1 = "My /ᐠ｡ꞈ｡ᐟ\\ is pretty (=ಠᆽಠ=) with me right now.";
    assert(replaceWords(input1) == expected1);

    std::string input2 = "I love my kitten, and my kitten loves me.";
    std::string expected2 = "I (₌♥ᆽ♥₌) my (•ㅅ•), and my kitten loves me.";
    assert(replaceWords(input2) == expected2);

    std::string input3 = "Yarn is fun, but dancing is better!";
    std::string expected3 = "o~ is fun, but ~( ˘▾˘ ~) is better!";
    assert(replaceWords(input3) == expected3);

    std::cout << "All tests passed successfully!\n";
}

int main() {
    test_replaceWords();
    return 0;
}
