#ifndef _DECIDER_H
#define _DECIDER_H
#include "formula.h"
#include "utils.h"
#include <vector>
#include <string>
#include <unordered_map>
typedef vector<Formula*> Formula_List;

typedef enum{
    Hyp = 1,
    MP = 2,
    Ax1 = 3,
    Ax2 = 4,
    Ax3 = 5,
    Ax3_fix = 6
} Rule;

struct Annotation{
    Rule rule;
    int l1; //p-q  MP
    int l2; //p    MP
    Formula * a; // Ax2, Ax1, Ax3
    Formula * b; // Ax2, Ax1, 
    Formula * c; // Ax2

    //axiom flags
    bool flag_ax2_e; //it was created as a result of expansion using axiom2, so must not be considered for further expansion
    bool flag_ax2_sp;   // whether it was considered for axiom2special closure(), B candidates are from (last proof size -> end), 
                        // o/w from 0->end
    bool flag_lhs_axiom;//lhs is an axiom

//methods
    void print();
    Annotation();
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
    vector<bool> hypothesis_validity_list; //Taking (X-F) to rhs to generate simpler hyp invalidates (X-F)
    Formula_List Seed;//Seed to axioms(apart from formula in stmts of proof)
    Proof_Map proof; //statements which are lines in the proof in that order

    /* functions */
    Decider(Formula * stmt, Formula_List tSeed);
    ~Decider();
    void genererate_hypothesis(Formula *stmt, Formula_List & hyp_list, vector<bool>& hyp_validity);  //prove stmt S : equiv to proving: f1,f2,f3,...fn |- F
                                                //puts f1,f2,... in hypothesis_list
    void print_formula_list(Formula_List &l);
    void prove();

    //closure functions
    
    void lhs_some_axiom_closure(); //if lhs of some formula is an axiom, add the axiom to list
                                   //and set flag lhs_axiom=true,  so that we never try to prove its lhs
    void lhs_axiom3_lhs();
    void mp_closure(); //Modus ponens closure on proof
    void mp_closure_onepass(); //Modus ponens closure on proof
    void axiom1_closure();  // Axiom1 closure
    void axiom1_closure_brute();  // Axiom1 closure

    void axiom2_closure_expansion();  // Axiom2 closure
    void axiom2_closure_reduction();  // Axiom2 closure
    void axiom2_closure_special();  // Axiom2 closure
    void axiom2_closure_brute();  // Axiom2 closure

    void axiom3_closure(); // Axiom3 closure
    void axiom3_closure_brute(); // Axiom3 closure brute

};
#endif


