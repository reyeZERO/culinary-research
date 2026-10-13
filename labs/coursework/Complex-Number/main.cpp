#include "ComplexNumber.h"

int main() {
    ComplexNumber numberOne(5.0, 7.0);
    ComplexNumber numberTwo(2.5, 3.1);

    ComplexNumber numberThree = numberOne.add(numberTwo);
    numberThree.prettyPrint();

    ComplexNumber numberFour = numberOne.subtract(numberTwo);
    numberFour.prettyPrint();

    float magnitude = numberOne.magnitude();
    std::cout << magnitude << std::endl;

    return 0;
}
