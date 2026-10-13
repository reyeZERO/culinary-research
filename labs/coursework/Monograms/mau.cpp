#include <iostream>
#include <string>
using namespace std;

int main() {
    string first, middle, last;
    char separator;
    
    cout << "Welcome to the Monogram Program!\n" << endl;

    cout << "What are your initials (first, middle, and last)? ";
    cin >> first >> middle >> last;

    cout << "\nDo you want to use (s)paces or (p)eriods? ";
    cin >> separator;
    
    string monogram = "";
    monogram += toupper(middle[0]);
    monogram += (separator == 's') ? " " : ".";
    monogram += tolower(first[0]);
    monogram += (separator == 's') ? " " : ".";
    monogram += toupper(last[0]);

    cout << "\nYour monogram will be: " << monogram << endl;
    
    cout << "\nThank you for using the Monogram Program!" << endl;
    
    return 0;
}
