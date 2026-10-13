
#include <iostream>
#include <cmath>
#include <string>
#include <limits>
using namespace std;

int main() {
    int maxOccupancy, currentPeople;
    string input;

    cout << "Welcome to the Room Capacity Program!\n";
    
    // Prompt for maximum room capacity
    cout << "How many people can this room hold?: ";
    while (true) {
        cin >> maxOccupancy;
        if (cin.fail() || maxOccupancy <= 0) {
            cout << "That is not a valid value.\nPlease try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "How many people can this room hold?: ";
        } else {
            break; // Valid input
        }
    }

    int totalPeople = 0; // Initialize total people in the room

    while (true) {
        // Prompt for number of people arriving
        cout << "How many people have arrived for the meeting? (Type 'exit' to stop): ";
        cin >> input;

        if (input == "exit") {
            break; // Exit the loop
        }

        try {
            currentPeople = stoi(input); // Convert input to integer
            if (currentPeople < 0) {
                cout << "That is not a valid value. Please enter a positive number.\n";
                continue;
            }
        } catch (exception&) {
            cout << "That is not a valid value. Please enter a number.\n";
            continue;
        }

        totalPeople += currentPeople; // Update total number of people in the room

        // Display the current status
        double percentageUsed = (static_cast<double>(totalPeople) / maxOccupancy) * 100;
        cout << "You have used up " << round(percentageUsed) << "% of your room's capacity.\n";

        if (totalPeople <= maxOccupancy) {
            cout << "You still have room for " << maxOccupancy - totalPeople << " more people.\n";
            cout << "This meeting is LEGAL - proceed with the congregation!\n";
        } else {
            cout << "Some people have to leave.\n";
            cout << "This meeting is NOT LEGAL - you need to break it up!\n";
        }
    }

    cout << "\nThank you for using the Room Capacity Program!\n";
    return 0;
}


