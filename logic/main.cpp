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
    for(int i=0; i<seed_count; i++){
        seeds.push_back(parse());
    }

    cout << endl <<"** Decider **" <<endl;
    Decider Dec(Axiom2(f1, f2, f3), seeds);



    cout << "- - - - - test - - - - - - " <<endl;
    Proof_Map pm;
    pm.push(f1);
    pm.push(f2);
    Formula * x = pm.get(f2->to_string());//->print_line();
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

