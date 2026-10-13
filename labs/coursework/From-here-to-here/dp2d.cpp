#include <iostream>
#include <cmath>
using namespace std;
int main() {
    double x1, y1;
    double x2, y2;
    cout<<"Welcome to the 2D Distance Program!\n";
    cout<<"What is the first point in the plane?\n";
    cin>>x1>>y1;
    cout<<"What is the second point in the plane?\n";
    cin>>x2>>y2;
    cout<<"Calculating the distance now....\n";
    cout<<"The distance between ("<<x1<<","<<y1<<") and ("<<x2<<","<<y2<<") is "<<sqrt(pow((x2-x1),2)+pow((y2-y1),2))<<"\n";
    cout<<"Thank you for using the 2D Distance Program.\n";
    cout << R"(  
                   ,,,, 
             ,;) .';;;;',
 ;;,,_,-.-.,;;'_,|I\;;;/),,_
  `';;/:|:);{ ;;;|| \;/ /;;;\__
      L;/-';/ \;;\',/;\/;;;.') \
      .:`''` - \;;'.__/;;;/  . _'-._ 
    .'/   \     \;;;;;;/.'_7:.  '). \_
  .''/     | '._ );}{;//.'    '-:  '.,L
.'. /       \  ( |;;;/_/         \._./;\   _,
 . /        |\ ( /;;/_/             ';;;\,;;_,
. /         )__(/;;/_/                (;;'''''
 /        _;:':;;;;:';-._             );
/        /   \  `'`   --.'-._         \/
       .'     '.  ,'         '-,
      /    /   r--,..__       '.\
    .'    '  .'        '--._     ]
    (     :.(;>        _ .' '- ;/
    |      /:;(    ,_.';(   __.'
     '- -'"|;:/    (;;;;-'--'
           |;/      ;;(
 snd       ''      /;;|
                   \;;|
         
         )"<<'\n';


    return 0;
}