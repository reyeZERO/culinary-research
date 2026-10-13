#include <iostream>
#include <string>
#include "time_calculator.h"

int main() {
    std::string time1, time2;
    int choice;

    std::cout << "Welcome to the Time Interval Calculation Program!\n\n";
    std::cout << "Do you want the time interval to be:\n(1) Inclusive\n(2) Exclusive\n";
    std::cin >> choice;

    do {
        std::cout << "\nWhat is your first time? (HH:MM) ";
        std::cin >> time1;
    } while (!isValidTime(time1));

    do {
        std::cout << "\nWhat is your second time? (HH:MM) ";
        std::cin >> time2;
    } while (!isValidTime(time2));

    int minutes = calculateMinutes(time1, time2, choice == 1);
    int hours = minutes / 60;
    int remainingMinutes = minutes % 60;
    double decimalHours = minutes / 60.0;

    std::cout << "\nThe time interval can be written as:\n";
    std::cout << "  * " << minutes << " minutes\n";
    std::cout << "  * " << hours << " hours and " << remainingMinutes << " minutes.\n";
    std::cout << "  * " << decimalHours << " hours\n";

    std::cout << "\nThank you for using the Time Interval Calculation Program.\n";
    return 0;
}
