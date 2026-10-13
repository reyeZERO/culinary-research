#include <string>

std::string number_suffix(int n, bool include_number = false) {
    if (n <= 0) return "";

    int last_two = n % 100;
    int last = n % 10;

    std::string suffix;
    if (last_two >= 11 && last_two <= 13) {
        suffix = "th";
    } else if (last == 1) {
        suffix = "st";
    } else if (last == 2) {
        suffix = "nd";
    } else if (last == 3) {
        suffix = "rd";
    } else {
        suffix = "th";
    }

    if (include_number) {
        return std::to_string(n) + suffix;
    }
    return suffix;
}
