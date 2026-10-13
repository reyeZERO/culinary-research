#include <iostream>
#include <string>
#include "statistics.h"

int main() {
    std::cout << "Welcome to the Number Statistics Program!\n" << std::endl;

    std::string filename;
    std::cout << "Please enter the name of your data file: ";
    std::getline(std::cin, filename);

    int count;
    double mean, stddev, min, max;

    while (!process_file(filename, count, mean, stddev, min, max)) {
        std::cout << "I'm sorry, I could not open '" << filename << "' or the file is empty.\n" << std::endl;
        std::cout << "Please enter another name: ";
        std::getline(std::cin, filename);
    }

    std::cout << "\nFile '" << filename << "' opened successfully!" << std::endl;
    std::cout << "Reading data from '" << filename << "'..." << std::endl;
    std::cout << "Calculating..." << std::endl;
    std::cout << "Done processing data!\n" << std::endl;

    std::cout << "For your data, the statistics are as follows:\n" << std::endl;
    std::cout << "     Count:  " << count << std::endl;
    std::cout << "   Minimum:  " << min << std::endl;
    std::cout << "      Mean:  " << mean << std::endl;
    std::cout << "   Maximum:  " << max << std::endl;
    std::cout << "    StdDev:  " << stddev << std::endl;

    std::cout << "\nThank you for using the Number Statistics Program!" << std::endl;

    return 0;
}
