#include <iostream>
#include <cstdlib> // for rand()
using namespace std;
int main() {
    srand(time(0));
    int x = 0;
    int numd, numf, mod;
    int roll = 0;
    char d;
    cout<<"Welcome to the Dice Statistics Program!\n"<<"\n";
    while (true) {
    cout<<"Would you like to roll?\n" <<"1.Yes\n"<<"2.No\n"<<"\n";
    cout<<":";
    cin>> x;
    if (x == 2) {
        break;
    }
    cout<<"What is your roll? "<<"\n"<<"\n";
    cin>>numd>>d>>numf;
    cout<<"\n";
    cout<<"What is the constant modifier you want to add to the roll\n"<<"\n";
    cin>>mod;
    cout<<"\n"<<"\n";
    cout<<"Thank you! When rolling a "<<numd<<d<<numf<<" + "<<mod<<", your statistics will be:\n"<<"\n"<<"\n";
    cout<<"   Minimum:  "<<numd<<"\n";
    cout<<"   Average:  "<<(static_cast<double>(numd)+(static_cast<double>(numd)*static_cast<double>(numf)))/2<<"\n";
    cout<<"   Maximum:  "<<numd*numf<<"\n"<<"\n";
    for (int i=1; i <= numd; ++i) {
        int rv = rand()% numf + 1;
        roll += rv;
        
    }
    cout<<"Your rolled a "<<roll<<"."<<"\n"<<"\n";
    }
    cout<<"Thank you for using DSP";cout<<"\n"<<"\n";

    return 0;
}