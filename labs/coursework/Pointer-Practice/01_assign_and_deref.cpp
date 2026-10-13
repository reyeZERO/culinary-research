#include <iostream>
using namespace std;

int main() {
  int a, b;
  cout << "Enter two integers (a b): ";
  if (!(cin >> a >> b)) return 0;

  int* ptr_a = &a;
  int* ptr_b = &b;

  cout << "*ptr_a = " << *ptr_a << "\n";
  cout << "*ptr_b = " << *ptr_b << "\n";
}
