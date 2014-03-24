#include "formula.h"
#include <string>
using namespace std;

Formula::Formula(){
    lhs = NULL;
    rhs = NULL;
    val = '-';
    str_form = "?"; //empty
}

Formula::Formula(char tval, Formula * tlhs, Formula * trhs){ //non-leaf
    lhs = tlhs;
    rhs = trhs;
    val = tval;
    len = tlhs->len + trhs->len;
}

Formula::Formula(char tval){ //leaf
    lhs = NULL;
    rhs = NULL;
    val = tval;
    len = 1;
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

string Formula::to_string(){
    if(str_form == "?"){
        print_string(str_form);
    }
    else{
        cout << "reusing ..... " <<endl;
    }
    return str_form;
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

bool Formula::is_leaf(){
    if(val=='-') return false;
    return true;
}

bool Formula::is_false(){
    if(val=='F') return true;
    return false;
}

Formula* Formula::copy(){ //shalow copy
    if(is_leaf()){
        if(val == 'F') return TheFalse;
        else return new Formula(val);
    }
    return new Formula(val, lhs, rhs);
}
