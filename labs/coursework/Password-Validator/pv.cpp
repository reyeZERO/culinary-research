#include <iostream>
#include <cctype>
#include <string>
#include <cassert>

using namespace std;

bool valid_password(const string &password) {
    if (password.length() < 8) {
        cout << "The password must be at least 8 characters" << endl;
        return false;
    }

    int digit_count = 0, special_count = 0, capital_count = 0;
    string special_chars = "!@#$%^&*()-+=<>?/{}[]|";

    for (char ch : password) {
        if (isdigit(ch)) digit_count++;
        if (isupper(ch)) capital_count++;
        if (special_chars.find(ch) != string::npos) special_count++;
    }

    if (digit_count < 2) {
        cout << "The password must contain at least 2 numbers" << endl;
        return false;
    }

    if (capital_count < 1) {
        cout << "The password must contain at least 1 capital letter" << endl;
        return false;
    }

    if (special_count < 1) {
        cout << "The password must contain at least 1 special character" << endl;
        return false;
    }

    return true;
}

int main() {
    // Test cases
    assert(!valid_password("Short1!")); // Too short
    assert(!valid_password("onlylowercase1!")); // No capital letter
    assert(!valid_password("NOCAPS123!")); // No lowercase
    assert(!valid_password("Valid1!")); // Too short
    assert(!valid_password("Longpasswordwithoutnumbers!")); // No numbers
    assert(!valid_password("LongPasswordWithoutSpecial123")); // No special characters
    assert(valid_password("ValidPass123!")); // Valid password

    cout << "All tests passed!" << endl;
    return 0;
}
