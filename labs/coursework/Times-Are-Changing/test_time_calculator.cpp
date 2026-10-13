#include "time_calculator.h"
#include <iostream>
#include <sstream>
#include <iomanip>

bool isValidTime(const std::string &time) {
    int hours, minutes;
    char colon;
    std::istringstream ss(time);
    if (ss >> hours >> colon >> minutes && colon == ':' && hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60) {
        return true;
    }
    std::cout << "That is not a valid time!\n";
    return false;
}

int convertToMinutes(const std::string &time) {
    int hours, minutes;
    char colon;
    std::istringstream ss(time);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

int calculateMinutes(const std::string &time1, const std::string &time2, bool inclusive) {
    int startMinutes = convertToMinutes(time1);
    int endMinutes = convertToMinutes(time2);
    return inclusive ? (endMinutes - startMinutes + 1) : (endMinutes - startMinutes);
}
