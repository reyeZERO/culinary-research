#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    const int SIZE = 5;
    int arr[SIZE] = {10, 20, 30, 40, 50};

    int index;
    cout << "Enter an index (0 to " << SIZE - 1 << "): ";
    cin >> index;

    try {
        if (index < 0 || index >= SIZE)
            throw out_of_range("Index is out of bounds!");

        cout << "Value at index " << index << " is " << arr[index] << endl;
    } 
    catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
        cout << "Please enter a valid index next time." << endl;
    }

    return 0;
}
