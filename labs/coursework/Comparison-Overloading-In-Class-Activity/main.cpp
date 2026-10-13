class ComplexNumber {
public:
    int real;
    int im;

    ComplexNumber(int x, int y) {
        real = x;
        im = y;
    }

    ComplexNumber operator+(const ComplexNumber& num) {
        return ComplexNumber(real + num.real, im + num.im);
    }

    ComplexNumber operator-(const ComplexNumber& num) {
        return ComplexNumber(real - num.real, im - num.im);
    }

    ComplexNumber operator*(const ComplexNumber& num) {
        return ComplexNumber(real * num.real - im * num.im, real * num.im + num.real * im);
    }

    bool operator<(const ComplexNumber& num) const {
        if (real < num.real)
            return true;
        else if (real == num.real)
            return im < num.im;
        else
            return false;
    }

    bool operator==(const ComplexNumber& num) const {
        return real == num.real && im == num.im;
    }

    bool operator!=(const ComplexNumber& num) const {
        return !(*this == num);
    }

    bool operator>(const ComplexNumber& num) const {
        return num < *this;
    }

    bool operator<=(const ComplexNumber& num) const {
        return !(*this > num);
    }

    bool operator>=(const ComplexNumber& num) const {
        return !(*this < num);
    }

    void pretty_print() const {
        cout << real << " + " << im << "i" << endl;
    }
};
