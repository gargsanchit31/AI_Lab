#ifndef _DECIDER_H
#define _DECIDER_H
#include "formula.h"
#include "utils.h"
#include <vector>
#include <string>
#include <unordered_map>
typedef vector<Formula*> Formula_List;

struct Proof_Map{
    unordered_map<string, int> map;
    Formula_List stmt_list;
    void push(Formula* f);
    Formula * get(string key);
};

class Decider{
public:
    Formula * statement; //that needs to be proved
    Formula_List hypothesis_list;
    Proof_Map proof; //statements which are lines in the proof in that order

    /* functions */
    Decider(Formula * stmt);
    void genererate_hypothesis(Formula *stmt, Formula_List & hyp_list);  //prove stmt S : equiv to proving: f1,f2,f3,...fn |- F
                                                //puts f1,f2,... in hypothesis_list
    void print_formula_list(Formula_List &l);
};
#endif


