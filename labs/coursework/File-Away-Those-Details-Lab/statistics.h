#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>

bool process_file(const std::string& filename, int& count, double& mean, double& stddev, double& min, double& max);

#endif
