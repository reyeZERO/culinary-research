#include <iostream>
using namespace std;

int main() {
  // Sample unsorted data (you can change the values or generate with rand()).
  int arr[] = {17, -3, 42, 8, 42, 0, 19, 5, 41, 2};
  const size_t N = sizeof(arr) / sizeof(arr[0]);

  int* begin = arr;
  int* end   = arr + N;       // one past the last
  int* max_ptr = begin;

  for (int* p = begin; p < end; ++p) {
    if (*p > *max_ptr) max_ptr = p;
  }

  cout << "Max value = " << *max_ptr
       << ", at index = " << (max_ptr - begin) << "\n";
}
