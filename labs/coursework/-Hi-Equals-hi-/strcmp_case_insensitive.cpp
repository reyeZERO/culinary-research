#include <iostream>
#include <cctype> 

int strcmp_case_insensitive(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        char c1 = std::tolower(static_cast<unsigned char>(*s1));
        char c2 = std::tolower(static_cast<unsigned char>(*s2));

        if (c1 != c2) {
            return c1 - c2; 
        }

        ++s1;
        ++s2;
    }
    return std::tolower(static_cast<unsigned char>(*s1)) -
           std::tolower(static_cast<unsigned char>(*s2));
}

int main() {
    const char* a = "Hi";
    const char* b = "hi";
    const char* c = "Hello";

    std::cout << "Comparison of \"Hi\" and \"hi\": " 
              << strcmp_case_insensitive(a, b) << std::endl;

    std::cout << "Comparison of \"Hi\" and \"Hello\": " 
              << strcmp_case_insensitive(a, c) << std::endl;

    std::cout << "Comparison of \"hi\" and \"Hi\": " 
              << strcmp_case_insensitive(b, a) << std::endl;

    return 0;
}
