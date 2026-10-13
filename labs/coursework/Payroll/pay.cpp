#include <iostream>
#include <string>
using namespace std;

int main() {
    double hours, rate = 16.78, gross, net;
    int dependents;
    string name;
    
    cout << "Welcome to the Payroll Program!\n";
    cout << "Enter employee name: ";
    getline(cin, name);
    cout << "Enter hours worked: ";
    cin >> hours;
    cout << "Enter number of dependents: ";
    cin >> dependents;
    
    if (dependents < 0) dependents = 0;
    double insurance = (dependents >= 3) ? 35.00 : 15.00;
    double overtime = (hours > 40) ? (hours - 40) * (rate * 1.5) : 0;
    gross = (hours <= 40 ? hours * rate : 40 * rate) + overtime;
    
    double tax = gross * 0.25;
    double unionDues = 10.00;
    net = gross - tax - unionDues - insurance;
    
    cout << "\nPayroll Stub:\n";
    cout << "Employee: " << name << "\n";
    cout << "Hours: " << hours << "\nRate: $" << rate << "/hr\n";
    cout << "Gross Pay: $" << gross << "\n";
    cout << "Taxes: $" << tax << "\nUnion Dues: $" << unionDues << "\nInsurance: $" << insurance << "\n";
    cout << "Net Pay: $" << net << "\n";
    cout << "Thank you for using the Payroll Program!" << endl;
    
    return 0;
}
