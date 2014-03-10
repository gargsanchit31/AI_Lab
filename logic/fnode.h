#include <iostream>

class FNode{ //leaf has values a-z or A-Z
             //inner nodes has '-' value meaning an implication
public:
    FNode * lhs;
    FNode * rhs;
    char val;

    FNode();
    FNode(char tval, FNode * tlhs, FNode * trhs);
    FNode(char tval);
    void print();
};
