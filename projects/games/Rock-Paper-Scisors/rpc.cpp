#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getComputerChoice() {
    return rand() % 3 + 1;
}

string getChoiceName(int choice) {
    if (choice == 1) return "Rock";
    if (choice == 2) return "Paper";
    return "Scissors";
}

string getWinner(int user, int computer) {
    if (user == computer) return "It's a tie!";
    if ((user == 1 && computer == 3) || (user == 2 && computer == 1) || (user == 3 && computer == 2))
        return "You win!";
    return "Computer wins!";
}

int main() {
    srand(time(0));
    while (true) {
        cout << "\nRock, Paper, Scissors! Pick one:\n1) Rock\n2) Paper\n3) Scissors\n> ";
        int userChoice;
        cin >> userChoice;
        if (userChoice < 1 || userChoice > 3) {
            cout << "Invalid choice. Try again." << endl;
            continue;
        }
        int computerChoice = getComputerChoice();
        cout << "You: " << getChoiceName(userChoice) << " | Computer: " << getChoiceName(computerChoice) << endl;
        cout << getWinner(userChoice, computerChoice) << endl;
        cout << "Play again? (1 = Yes, 2 = No): ";
        int playAgain;
        cin >> playAgain;
        if (playAgain != 1) {
            cout << "Goodbye!" << endl;
            break;
        }
    }
    return 0;
}
