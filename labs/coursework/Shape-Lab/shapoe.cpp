#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
using namespace std;

class Shape {
public:
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual string getName() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getArea() const override {
        return M_PI * radius * radius;
    }
    double getPerimeter() const override {
        return 2 * M_PI * radius;
    }
    string getName() const override { return "Circle"; }
};

class Rectangle : public Shape {
protected:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() const override {
        return width * height;
    }
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    string getName() const override { return "Rectangle"; }
};

class Square : public Rectangle {
public:
    Square(double side) : Rectangle(side, side) {}
    string getName() const override { return "Square"; }
};

class RightTriangle : public Shape {
protected:
    double base, height;
public:
    RightTriangle(double b, double h) : base(b), height(h) {}
    double getArea() const override {
        return 0.5 * base * height;
    }
    double getPerimeter() const override {
        double hyp = sqrt(base * base + height * height);
        return base + height + hyp;
    }
    string getName() const override { return "RightTriangle"; }
};

class IsoscelesRightTriangle : public RightTriangle {
public:
    IsoscelesRightTriangle(double leg) : RightTriangle(leg, leg) {}
    string getName() const override { return "IsoscelesRightTriangle"; }
};

void printAreaToScreen(Shape *s) {
    cout << "The area of the " << s->getName() << " is " << s->getArea() << endl;
}

int main() {
    Circle c(1.0);
    assert(fabs(c.getArea() - M_PI) < 1e-6);
    assert(fabs(c.getPerimeter() - 2 * M_PI) < 1e-6);

    Rectangle r(2.0, 3.0);
    assert(r.getArea() == 6.0);
    assert(r.getPerimeter() == 10.0);

    Square s(4.0);
    assert(s.getArea() == 16.0);
    assert(s.getPerimeter() == 16.0);

    RightTriangle rt(3.0, 4.0);
    assert(rt.getArea() == 6.0);
    assert(fabs(rt.getPerimeter() - 12.0) < 1e-6);

    IsoscelesRightTriangle irt(2.0);
    assert(fabs(irt.getArea() - 2.0) < 1e-6);
    assert(fabs(irt.getPerimeter() - (2.0 + 2.0 + sqrt(8.0))) < 1e-6);

    printAreaToScreen(&c);
    printAreaToScreen(&r);
    printAreaToScreen(&s);
    printAreaToScreen(&rt);
    printAreaToScreen(&irt);

    cout << "All tests passed successfully!" << endl;
    return 0;
}
