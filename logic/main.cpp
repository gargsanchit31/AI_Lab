#include <iostream>
#include "fnode.h"
#include "utils.h"
using namespace std;


int main(){
    FNode * f1 = parse();
    f1->print();cout <<endl;

    FNode * f2 = parse();
    f2->print();cout <<endl;

    cout << (*f1 == *f2) <<endl;
    /*
    cout << "****" <<endl;
    FNode * l = new FNode('a');
    FNode * r = new FNode('b');
    FNode * f = new FNode('-',l,r);
    f->print(); cout<< endl;
    */
}

