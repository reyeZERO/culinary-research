#include <cassert>
#include "palindrome.h"

int main() {
    assert(is_palindrome("Rotavator"));
    assert(is_palindrome("x"));
    assert(is_palindrome("mom"));
    assert(!is_palindrome("Sam"));
    assert(!is_palindrome("orange"));
    assert(!is_palindrome("flower"));
    return 0;
}
