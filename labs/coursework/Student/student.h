#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string first_name;
    std::string last_name;
    const int student_id;
    int number_of_credits;

    static int generate_student_id();

public:
    Student(std::string first, std::string last);
    
    std::string get_first_name() const;
    void set_first_name(std::string first);
    
    std::string get_last_name() const;
    void set_last_name(std::string last);
    
    int get_student_id() const;
    int get_number_of_credits() const;
    
    void add_credits(int number);
    void reset_credits();
};

#endif
