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

    cout << "Printing Ax2 String : " << (Axiom2(f1, f2, f3)->to_string()) <<endl;

    //Take Seed formulae
    int seed_count;
    cin >> seed_count;
    Formula_List seeds;
    Proof_Map pm;
    for(int i=0; i<seed_count; i++){
        Formula * f = parse();
        seeds.push_back(f);
        pm.push(f);
    }

    cout << endl <<"** Decider **" <<endl;
    Decider Dec(Axiom2(f1, f2, f3), seeds);
    cout << "Testing MP closure " << endl;
    Dec.proof = pm;
    cout << "Before " <<endl;
    Dec.print_formula_list(Dec.proof.stmt_list);
    Dec.mp_closure();
    cout << "After " <<endl;
    Dec.print_formula_list(Dec.proof.stmt_list);
    



    cout << "- - - - - test - - - - - - " <<endl;
    Proof_Map pm1;
    pm1.push(f1);
    pm1.push(f2);
    Formula * x = pm1.get(f2->to_string());//->print_line();
    if(x != NULL){
        x->print_line();
    }

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

