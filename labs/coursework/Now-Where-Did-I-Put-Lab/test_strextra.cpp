#include "strextra.h"
#include <cassert>
#include <iostream>

int main() {
    using strextra::find;

    assert(find("The quick brown fox", 'e') == 2);
    assert(find("The quick brown fox", "e") == 2);
    assert(find("The quick brown fox", ' ') == 3);
    assert(find("The quick brown fox", "quick") == 4);
    assert(find("The quick brown fox", "quiet") == -1);

    assert(find("The quick brown fox", "cow") == 7);
    assert(find("The quick brown fox", "hix") == 1);
    assert(find("11112", "112") == -1);

    assert(find("dumb", 'd', 0) == 0);
    assert(find("lamb", 'q', 0) == -1);
    assert(find("pits", 'i', 2) == -1);
    assert(find("help", 'h', 5) == -1);
    assert(find("+1.4", "4", 3) == 3);
    assert(find("take", "ake", 0) == 1);
    assert(find("lean", 'n', 3) == 3);
    assert(find("3.14", "14", 0) == 2);
    assert(find("wall", "wa", 1) == -1);

    assert(find("Hi", 'h', 0, false) == 0);
    assert(find("Hi", "hi", 0, false) == 0);
    assert(find("Alphabet", "BET", 0, false) == 5);
    assert(find("ßeta", "ss", 0, false) == -1);

    assert(find("dumb bunnies", "??mb") == 0);
    assert(find("lamb", "??mb") == 0);
    assert(find("lamb", "*mb") == 0);
    assert(find("lamb", "?mb") == 1);
    assert(find("pits", "*s") == 0);
    assert(find("help", "hel?") == 0);
    assert(find("yellow", "y*l") == 0);
    assert(find("that's why I like milk", "y*l") == 9);
    assert(find("What's that?", "/?") == 11);
    assert(find("pretty *'s", "/*") == 7);
    assert(find("/home/students", "//") == 0);
    assert(find("dumb", "*d") == 0);
    assert(find("dumb", "b*") == 3);

    assert(find("dumb bunnies", "b*b*n") == 3);
    assert(find("dumb bunnies", "b*n*n") == 3);
    assert(find("dumb bunnies", "u*n*n") == 1);
    assert(find("baaab", "b*a*b") == 0);
    assert(find("aaaaa", "*a*a*") == 0);

    assert(find("", "", 0) == 0);
    assert(find("", "a", 0) == -1);
    assert(find("abc", "", 2) == 2);
    assert(find("abc", 'c', 3) == -1);

    std::cout << "OK\n";
    return 0;
}
