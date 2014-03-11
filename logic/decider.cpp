#include "decider.h"

Decider::Decider(Formula * stmt){
    statement = stmt;
    genererate_hypothesis(statement, hypothesis_list);
    print_formula_list(hypothesis_list);

    proof.assign(hypothesis_list.begin(), hypothesis_list.end());//all hyp are also lines in proof
    print_formula_list(proof);
}

void Decider::genererate_hypothesis(Formula * stmt, Formula_List& hyp_list){
    if(stmt->is_leaf()){//generate a-F
        Formula* hyp = implication(stmt, new Formula('F'));
        hyp_list.push_back(hyp);
    }
    else{//stmt is (lhs-rhs) , so push lhs to hyp_list, recurse on rhs
        hyp_list.push_back(stmt->lhs);
        genererate_hypothesis(stmt->rhs, hyp_list);
    }
}

void Decider::print_formula_list(Formula_List &l){
    for(int i=0; i<l.size(); i++){
        cout << i << " : ";
        l[i]->print_line();
    }
}
