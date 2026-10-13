#include "student.h"
#include <cstdlib>
#include <ctime>

// Function to generate a random student ID
int Student::generate_student_id() {
    return 100000 + (std::rand() % 900000);
}

// Constructor
Student::Student(std::string first, std::string last)
    : first_name(first), last_name(last), student_id(generate_student_id()), number_of_credits(0) {}

// Getter and Setter for first name
std::string Student::get_first_name() const { return first_name; }
void Student::set_first_name(std::string first) { first_name = first; }

// Getter and Setter for last name
std::string Student::get_last_name() const { return last_name; }
void Student::set_last_name(std::string last) { last_name = last; }

// Getter for student ID (read-only)
int Student::get_student_id() const { return student_id; }

// Getter for number of credits (read-only)
int Student::get_number_of_credits() const { return number_of_credits; }

// Method to add credits
void Student::add_credits(int number) {
    if (number > 0) {
        number_of_credits += number;
    }
}

// Method to reset credits to zero
void Student::reset_credits() {
    number_of_credits = 0;
}
