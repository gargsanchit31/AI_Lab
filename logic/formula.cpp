#include "formula.h"
using namespace std;

Formula::Formula(){
    lhs = NULL;
    rhs = NULL;
    val = '-';
}

Formula::Formula(char tval, Formula * tlhs, Formula * trhs){
    lhs = tlhs;
    rhs = trhs;
    val = tval;
}

Formula::Formula(char tval){
    lhs = NULL;
    rhs = NULL;
    val = tval;
}

void Formula::print(){
    if(val == '-'){//recusively print lhs & rhs
        cout << "(";
        lhs->print();
        cout << "-";
        rhs->print();
        cout<<")";
    }
    else{//it's leaf
        cout << val;
    }
}

bool Formula::operator == (const Formula & node){
    if(val == node.val && val=='-'){
        //recusively check lhs and rhs
        return ((*lhs == *node.lhs) && (*rhs == *node.rhs));
    }
    else if(val == node.val){
        return true;
    }
    return false;
}
