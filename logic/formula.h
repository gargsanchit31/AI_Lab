#ifndef _FORMULA_H
#define _FORMULA_H
#include <iostream>
#include <string>
using namespace std;

class Formula{ //leaf has values a-z or A-Z
             //inner nodes has '-' value meaning an implication
public:
    Formula * lhs;
    Formula * rhs;
    char val;
    /* basic */
    Formula();
    Formula(char tval, Formula * tlhs, Formula * trhs);
    Formula(char tval);
    void print();
    void print_line();
    void print_string(string &buffer);
    bool operator == (const Formula & node);
};
#endif
