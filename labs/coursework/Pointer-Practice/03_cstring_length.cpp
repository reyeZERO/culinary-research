#include <iostream>
using namespace std;

int main() {
  char s[] = "pointer practice!";
  char* p = s;
  size_t len = 0;

  while (*p != '\0') { ++len; ++p; }
  cout << "Length = " << len << "\n";
}
