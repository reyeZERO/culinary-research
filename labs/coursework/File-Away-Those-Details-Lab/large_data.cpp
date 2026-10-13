
#include <fstream>

int main() {
    std::ofstream outfile("test_files/large_data.txt");
    for (int i = 1; i <= 1000; ++i) {
        outfile << i << " ";
    }
    outfile.close();
    return 0;
}
