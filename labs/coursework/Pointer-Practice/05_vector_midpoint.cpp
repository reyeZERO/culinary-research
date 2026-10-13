#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v{9, 4, 7, 12, 5, 1, 3}; // change values/length as you like

  if (v.empty()) { cout << "Vector is empty.\n"; return 0; }

  int* base  = v.data();
  int* left  = base;
  int* right = base + (v.size() - 1);

  while (left < right) { ++left; --right; }

  size_t idx;
  if (left == right) {                 // odd length: met exactly at midpoint
    idx = static_cast<size_t>(left - base);
  } else {                             // even length: they crossed; take smaller index
    idx = static_cast<size_t>(right - base);
  }

  cout << "Midpoint index = " << idx
       << ", value = " << *(base + idx) << "\n";
}
