#include <iostream>
#include <string>

int main() {
      double x, y;
      std::cout <<"Welcome to the Resistor Calculation Program!\n";
      std::cin >> x >> y;
      std::cout <<"Thank you! You have entered " << x <<" omhs and " << y <<" omhs.\n";
      //i make an error in this line above i write cuot instead of cout take me 5 min to realized.
      std::cout <<"if resistors are placed in series, they will total of  ";
      std::cout << x + y <<" omhs.\n";
      std::cout <<"If they are placed in parallel, they will total of "<< 1/(1/x)+(1/y) <<" omhs.\n";
      std::cout <<"Thank you for using RCP!\n";
      std::cout << R"(
      _     _             
       (_)   | |            
 _ __ ___  ___ _ ___| |_ ___  _ __ 
| '__/ _ \/ __| / __| __/ _ \| '__|
| | |  __/\__ \ \__ \ || (_) | |   
|_|  \___||___/_|___/\__\___/|_|
      
            )" << '\n';
      
          


	return 0;
}
