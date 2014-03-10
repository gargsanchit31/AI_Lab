#include <iostream>
#include "formula.h"
#include "utils.h"
using namespace std;


int main(){
    Formula * f1 = parse();
    f1->print();cout <<endl;

    Formula * f2 = parse();
    f2->print();cout <<endl;

    cout << (*f1 == *f2) <<endl;
    /*
    cout << "****" <<endl;
    Formula * l = new Formula('a');
    Formula * r = new Formula('b');
    Formula * f = new Formula('-',l,r);
    f->print(); cout<< endl;
    */
}
