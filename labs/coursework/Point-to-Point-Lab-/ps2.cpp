#include <iostream>
using namespace std;
int main() {
    double x1, y1;
    double x2, y2;
    cout<<"Welcome to the 2D Midpoint Program!\n";
    cout<<"What is the first point in the plane?\n";
    cin>>x1>>y1;
    cout<<"What is the second point in the plane?\n";
    cin>>x2>>y2;
    cout<<"Calculating the midpoint now...\n";
    cout<<"The midpoint of the line segment between ("<<x1<<","<<y1<<") and ("<<x2<<","<<y2<<") is ("<<((x1+x2)/2)<<","<<((y1+y2)/2)<<")\n";
    cout<<"Thank you for using the 2D Midpoint Program.\n";
    cout << R"(  
       \****__              ____                                              
         |    *****\_      --/  \-__                                          
         /_          (_    ./ ,/----'                                         
Art by     \__         (_./  /                                                
 Ironwing     \__           \___----^__                                       
               _/   _                  \                                      
        |    _/  __/ )\"\ _____         *\                                    
        |\__/   /    ^ ^       \____      )                                   
         \___--"                    \_____ ) 
         
         )"<<'\n';


    return 0;
}

