#include <iostream>
#include "fnode.h"
using namespace std;

FNode* parse(){ //formula is either 'a' OR (<f> - <f>)
    FNode * formula;
    formula = new FNode();

    char x;
    cin >> x;
    if(x != '('){//i.e its 'a'
        formula->val = x;
        return formula;
    }

    //its (f - f)
    FNode * lhs;
    FNode * rhs;
    lhs = parse();

    cin >>x ; //for '-'
    if(x != '-'){ //Error checking
        cout << "Found character '" << x <<"'. Expected '-'" <<endl;
        return NULL;
    }

    rhs = parse();

    cin >> x; //for ')'
    if(x != ')'){ //Error checking
        cout << "Found character '" << x <<"'. Expected ')'" <<endl;
        return NULL;
    }

    formula->lhs = lhs;
    formula->rhs = rhs;
    formula->val = '-';
    return formula;
}

int main(){
    FNode * fo = parse();
    fo->print();cout <<endl;
    cout << "****" <<endl;
    FNode * l = new FNode('a');
    FNode * r = new FNode('b');
    FNode * f = new FNode('-',l,r);
    f->print(); cout<< endl;
}

