#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(float r, float i) : real(r), imaginary(i) {}

float ComplexNumber::getReal() const { return real; }

float ComplexNumber::getImaginary() const { return imaginary; }

ComplexNumber ComplexNumber::add(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imaginary + other.imaginary);
}

ComplexNumber ComplexNumber::subtract(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imaginary - other.imaginary);
}

ComplexNumber ComplexNumber::multiply(const ComplexNumber& other) const {
    return ComplexNumber(real * other.real - imaginary * other.imaginary,
                         real * other.imaginary + imaginary * other.real);
}

ComplexNumber ComplexNumber::divide(const ComplexNumber& other) const {
    float denominator = other.real * other.real + other.imaginary * other.imaginary;
    return ComplexNumber((real * other.real + imaginary * other.imaginary) / denominator,
                         (imaginary * other.real - real * other.imaginary) / denominator);
}

ComplexNumber ComplexNumber::negate() const {
    return ComplexNumber(-real, -imaginary);
}

ComplexNumber ComplexNumber::conjugate() const {
    return ComplexNumber(real, -imaginary);
}

float ComplexNumber::magnitude() const {
    return std::sqrt(real * real + imaginary * imaginary);
}

float ComplexNumber::phase() const {
    return std::atan2(imaginary, real);
}

void ComplexNumber::prettyPrint() const {
    std::cout << real << " + " << imaginary << "i" << std::endl;
}
