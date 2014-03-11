#include "formula.h"
#include <string>
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

void Formula::print_line(){
    print();
    cout <<endl;
}

void Formula::print_string(string &buffer){
    if(val == '-'){//recusively print lhs & rhs
        buffer.push_back('(');
        lhs->print_string(buffer);
        buffer.push_back('-');
        rhs->print_string(buffer);
        buffer.push_back(')');
    }
    else{//it's leaf
        buffer.push_back(val);
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

