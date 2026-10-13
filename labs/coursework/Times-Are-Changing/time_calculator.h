#ifndef TIME_CALCULATOR_H
#define TIME_CALCULATOR_H

#include <string>

bool isValidTime(const std::string &time);
int calculateMinutes(const std::string &time1, const std::string &time2, bool inclusive);

#endif // TIME_CALCULATOR_H
