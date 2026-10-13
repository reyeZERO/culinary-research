#include <cassert>
#include <iostream>

std::string number_suffix(int n, bool include_number = false); // Declaration

int main() {
    // Basic tests
    assert(number_suffix(0) == "");
    assert(number_suffix(1) == "st");
    assert(number_suffix(2) == "nd");
    assert(number_suffix(3) == "rd");
    assert(number_suffix(4) == "th");
    assert(number_suffix(11) == "th");
    assert(number_suffix(12) == "th");
    assert(number_suffix(13) == "th");
    assert(number_suffix(21) == "st");
    assert(number_suffix(22) == "nd");
    assert(number_suffix(23) == "rd");
    assert(number_suffix(24) == "th");
    assert(number_suffix(112) == "th");
    assert(number_suffix(123, true) == "123rd");

    std::cout << "All tests passed!\\n";
    return 0;
}
