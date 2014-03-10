#include <iostream>
#include "fnode.h"
#include "utils.h"
using namespace std;


int main(){
    FNode * fo = parse();
    fo->print();cout <<endl;
    cout << "****" <<endl;
    FNode * l = new FNode('a');
    FNode * r = new FNode('b');
    FNode * f = new FNode('-',l,r);
    f->print(); cout<< endl;
}

