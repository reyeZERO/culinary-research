#include "student.h"
#include <iostream>
#include <cassert>
#include <ctime>

int main() {
    std::srand(std::time(0)); // Seed random number generator
    
    // Creating a student object
    Student student("Bob", "Bobberson");
    
    // Testing name getters
    assert(student.get_first_name() == "Bob");
    assert(student.get_last_name() == "Bobberson");
    
    // Testing initial credits
    assert(student.get_number_of_credits() == 0);
    
    // Adding credits
    student.add_credits(6);
    student.add_credits(2);
    assert(student.get_number_of_credits() == 8);
    
    // Resetting credits
    student.reset_credits();
    assert(student.get_number_of_credits() == 0);
    
    // Printing student details
    std::cout << "Student Name: " << student.get_first_name() << " " << student.get_last_name() << std::endl;
    std::cout << "Student ID: " << student.get_student_id() << std::endl;
    std::cout << "Credits: " << student.get_number_of_credits() << std::endl;
    
    std::cout << "All tests passed successfully!" << std::endl;
    
    return 0;
}
