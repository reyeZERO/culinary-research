#include "statistics.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <cmath>

bool process_file(const std::string& filename, int& count, double& mean, double& stddev, double& min, double& max) {
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        return false;
    }

    double value;
    double sum = 0.0;
    double sum_of_squares = 0.0;
    count = 0;
    min = std::numeric_limits<double>::max();
    max = std::numeric_limits<double>::lowest();

    while (infile >> value) {
        count++;
        sum += value;
        sum_of_squares += value * value;
        if (value < min) min = value;
        if (value > max) max = value;
    }

    infile.close();

    if (count == 0) {
        return false; // Empty file case
    }

    mean = sum / count;
    double variance = (sum_of_squares - (sum * sum) / count) / (count - 1);
    stddev = std::sqrt(variance);

    return true;
}
