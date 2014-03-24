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
    int len;
    /* basic */
    Formula();
    Formula(char tval, Formula * tlhs, Formula * trhs);
    Formula(char tval);
    void print();
    void print_line();
    void print_string(string &buffer);
    string to_string();
    bool operator == (const Formula & node);
    bool is_leaf();
    bool is_false(); //Is syntactically False
    Formula* copy(); //returns new Formula(val, lhs, rhs)
};

extern Formula* TheFalse;
#endif
