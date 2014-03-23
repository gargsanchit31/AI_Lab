#ifndef _DECIDER_H
#define _DECIDER_H
#include "formula.h"
#include "utils.h"
#include <vector>
#include <string>
#include <unordered_map>
typedef vector<Formula*> Formula_List;

typedef enum{
    Hyp,
    MP,
    Ax1,
    Ax2,
    Ax3
} Rule;

struct Annotation{
    Rule rule;
    int l1; //p-q  MP
    int l2; //p    MP
    Formula * a; // Ax2, Ax1, Ax3
    Formula * b; // Ax2, Ax1, 
    Formula * c; // Ax2
    void print();
};

typedef vector<Annotation> Annotation_List;

struct Proof_Map{
    unordered_map<string, int> map;
    Formula_List stmt_list; //Proof lines
    Annotation_List ann_list; //Explanation(annotate) each proof line
    int push(Formula* f, Annotation ann); //returns 0 if pushed, -1 if already exists
    int get(string key);
    void print(); //print annotated list of statements
    void print(int i); //print annotated list of statements
    void trace(); //trace back the steps to hyps
};

class Decider{
public:
    Formula * statement; //that needs to be proved
    Formula_List hypothesis_list;
    Formula_List Seed;//Seed to axioms(apart from formula in stmts of proof)
    Proof_Map proof; //statements which are lines in the proof in that order

    /* functions */
    Decider(Formula * stmt, Formula_List tSeed);
    void genererate_hypothesis(Formula *stmt, Formula_List & hyp_list);  //prove stmt S : equiv to proving: f1,f2,f3,...fn |- F
                                                //puts f1,f2,... in hypothesis_list
    void print_formula_list(Formula_List &l);
    void prove();

    //closure functions
    void mp_closure(); //Modus ponens closure on proof
    void mp_closure_onepass(); //Modus ponens closure on proof
    void axiom1_closure();  // Axiom1 closure
    void axiom2_closure();  // Axiom2 closure
    void axiom3_closure(); // Axiom3 closure
    void axiom3_closure_brute(); // Axiom3 closure brute

};
#endif


