#include "palindrome.h"
#include <cctype>

bool is_palindrome(const std::string& str) {
    int left = 0, right = str.length() - 1;
    while (left < right) {
        if (std::tolower(str[left]) != std::tolower(str[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
