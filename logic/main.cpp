#include <iostream>
#include "formula.h"
#include "utils.h"
#include "decider.h"
#include <cstring>
#include <fstream>
#include <istream>
using namespace std;
istream *inFile;


int main(int argc, char *argv[]){
    /*
    //checking isAxiom1(), isAxiom3(), isAxiom2()
    Formula* fnot = parse_new();
    fnot->print_line();
    cout << "length  " << (fnot->len) << "is Axiom 1 : " << isAxiom3(fnot) << endl;
    return 0;
    */
    /*
    //checking length functionality
    Formula* fnot = parse_new();
    fnot->print_line();
    cout << "length  " << (fnot->len) << endl;
    return 0;
    */
    /* 
    //checking parsing functionality
    Formula* fnot = parse_new();
    fnot->print_line();
    return 0;
    */

    /*
    //checking axiom 3 closure new
    Formula * a = new Formula('a');
    Formula * F = new Formula('F');
    Formula * A = implication(implication(a, F), F);   //  ((a-F)-F)
    Formula * inp = implication(implication(A, F), F); //((    A    -F)-F)
    Formula_List seeds1;
    Decider Dec1(F, seeds1);
    Annotation ann;
    ann.rule = Hyp;
    Dec1.proof.push(inp,ann); //push inp

    Dec1.axiom3_closure();
    Dec1.mp_closure();
    cout << "one pass" <<endl;
    Dec1.proof.print();
    Dec1.axiom3_closure();
    Dec1.mp_closure();
    cout << "second pass" <<endl;
    Dec1.proof.print();
    return 0;
    */

    ifstream inFile_file;
    inFile_file.open(argv[1], ios::in);
    if(!inFile_file.is_open()){
        cout << "can't open control file " << argv[1] <<endl;
        exit(0);
    }
    inFile = &inFile_file; //Note its importance
/*
    Formula * C = parse_new(cin);
    cout << C->to_string() <<endl;
    return 0;
    */
    Formula * f1 = parse_new(*inFile);
    //f1->print_line();

    //Take Seed formulae
    int seed_count;
    *inFile >> seed_count;

    Formula_List seeds;
    for(int i=0; i<seed_count; i++){
        Formula * f = parse_new(*inFile);
        seeds.push_back(f);
    }

    cout << endl <<"** Decider **" <<endl;

    Decider Dec(f1, seeds);
    cout << "Proving Now...." <<endl;
    Dec.prove();
    /*
    Dec.axiom2_closure_special();
    Dec.proof.print();
    cout << "2" << endl;
    Dec.axiom2_closure_special();
    Dec.proof.print();
    */


    //CLEANING UP
    //~Decider() will be called implicitly
    //delete TheFalse withing it at the last
    
    /*
    Proof_Map pm1;
    pm1.push(f1);
    pm1.push(f2);
    Formula * x = pm1.get(f2->to_string());//->print_line();
    if(x != NULL){
        x->print_line();
    }
    */

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
