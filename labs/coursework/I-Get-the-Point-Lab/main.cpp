#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Point {
private:
    double x, y;

public:
    Point(double x_val = 0.0, double y_val = 0.0) {
        x = x_val;
        y = y_val;
    }

    double get_x() const { return x; }
    double get_y() const { return y; }

    double operator-(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    Point operator/(const Point& other) const {
        return Point((x + other.x) / 2.0, (y + other.y) / 2.0);
    }

    Point operator*(double scalar) const {
        return Point(x * scalar, y * scalar);
    }

    double operator[](char axis) const {
        if (axis == 'x' || axis == 'X') return x;
        if (axis == 'y' || axis == 'Y') return y;
        throw invalid_argument("Invalid index: use 'x' or 'y'");
    }

    friend ostream& operator<<(ostream& out, const Point& p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};

int main() {
    cout << boolalpha;

    Point p1(3.2, 9.8);
    Point p2(5.5, -1.2);

    cout << "Distance: " << (p1 - p2) << endl;
    cout << "Equal: " << (p1 == p2) << endl;
    cout << "Not Equal: " << (p1 != p2) << endl;
    cout << "Midpoint: " << (p1 / p2) << endl;

    cout << "Multiply by 2: " << (p1 * 2) << endl;
    cout << "Multiply by -3: " << (p1 * -3) << endl;

    cout << "X coordinate: " << p1['x'] << endl;
    cout << "Y coordinate: " << p1['y'] << endl;
}
