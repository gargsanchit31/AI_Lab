#include <iostream>
#include "formula.h"
#include "utils.h"
#include "decider.h"
using namespace std;


int main(){
    Formula * f1 = parse();
    //f1->print_line();

    Formula * f2 = parse();
    //f2->print_line();

    Formula * f3 = parse();
    //f3->print_line();

    cout << (*f1 == *f2) <<endl;

    implication(f1,f2)->print_line();
    Axiom1(f1, f2)->print_line();
    Axiom2(f1, f2, f3)->print_line();
    Axiom3(f1)->print_line();

    string ax_str;
    Axiom2(f1, f2, f3)->print_string(ax_str);
    cout << "Printing Ax String : " << ax_str <<endl;

    Decider Dec(Axiom2(f1, f2, f3));
    /*
        Formula * Axiom1(Formula *A, Formula *B);
        Formula * Axiom2(Formula *A, Formula *B, Formula *C);
        Formula * Axiom3(Formula *A);
     */

    /*
    cout << "****" <<endl;
    Formula * l = new Formula('a');
    Formula * r = new Formula('b');
    Formula * f = new Formula('-',l,r);
    f->print(); cout<< endl;
    */
}

