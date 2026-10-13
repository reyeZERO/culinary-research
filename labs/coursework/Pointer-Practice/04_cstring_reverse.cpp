#include <iostream>
using namespace std;

int main() {
  char s[] = "CSC 122";
  char* start = s;
  char* p = s;

  // Walk to the null terminator.
  while (*p != '\0') ++p;
  // Step back to the last real character.
  --p;

  cout << "Reversed: ";
  while (p >= start) { cout << *p; --p; }
  cout << "\n";
}
