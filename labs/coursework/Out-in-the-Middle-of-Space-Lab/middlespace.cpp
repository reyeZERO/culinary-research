#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159265358979323846;

// Function to convert Cartesian coordinates to Spherical coordinates
void cartesianToSpherical(double x, double y, double z, double &r, double &theta, double &phi) {
    r = sqrt(x*x + y*y + z*z);
    theta = atan2(y, x); // theta = arctan(y/x)
    phi = acos(z / r); // phi = arccos(z/r)
}

// Function to convert Spherical coordinates to Cartesian coordinates
void sphericalToCartesian(double r, double theta, double phi, double &x, double &y, double &z) {
    x = r * cos(theta) * sin(phi);
    y = r * sin(theta) * sin(phi);
    z = r * cos(phi);
}

int main() {
    int choice;
    cout << "Welcome to the Point Conversion Program!\n";
    
    // Input choice for coordinate system
    do {
        cout << "Do you want to enter your coordinate in:\n";
        cout << "(1) Spherical Coordinates\n";
        cout << "(2) Cartesian Coordinates\n";
        cin >> choice;
        
        if (choice != 1 && choice != 2) {
            cout << "That is not a valid choice! Please enter 1 or 2.\n";
        }
    } while (choice != 1 && choice != 2);
    
    double x, y, z, r, theta, phi;
    
    if (choice == 1) {
        cout << "Enter your spherical coordinates (r, theta, phi) separated by spaces: ";
        cin >> r >> theta >> phi;
        
        sphericalToCartesian(r, theta, phi, x, y, z);
        
        cout << "\nYour point is as follows. Angles are in radians:\n";
        cout << "Spherical Coordinates: (" << r << ", " << theta << ", " << phi << ")\n";
        cout << "Cartesian Coordinates: (" << x << ", " << y << ", " << z << ")\n";
    } else {
        cout << "Enter your Cartesian coordinates (x, y, z) separated by spaces: ";
        cin >> x >> y >> z;
        
        cartesianToSpherical(x, y, z, r, theta, phi);
        
        cout << "\nYour point is as follows. Angles are in radians:\n";
        cout << "Spherical Coordinates: (" << r << ", " << theta << ", " << phi << ")\n";
        cout << "Cartesian Coordinates: (" << x << ", " << y << ", " << z << ")\n";
    }
    
    cout << "\nThank you for using the Point Conversion Program!\n";
    return 0;
}
