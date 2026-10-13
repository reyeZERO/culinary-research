#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <iostream>
#include <cmath>

class ComplexNumber {
private:
    float real;
    float imaginary;

public:
    ComplexNumber(float r = 0.0, float i = 0.0);
    float getReal() const;
    float getImaginary() const;
    ComplexNumber add(const ComplexNumber& other) const;
    ComplexNumber subtract(const ComplexNumber& other) const;
    ComplexNumber multiply(const ComplexNumber& other) const;
    ComplexNumber divide(const ComplexNumber& other) const;
    ComplexNumber negate() const;
    ComplexNumber conjugate() const;
    float magnitude() const;
    float phase() const;
    void prettyPrint() const;
};

#endif
