#include "decider.h"

/**  Decider **/
Decider::Decider(Formula * stmt, Formula_List tSeed){
    statement = stmt;
    genererate_hypothesis(statement, hypothesis_list);
    //print_formula_list(hypothesis_list);

    for(int i=0; i<hypothesis_list.size(); i++){
        proof.push(hypothesis_list[i]);
    }
    cout << "Hypo list" <<endl;
    print_formula_list(proof.stmt_list);

    Seed = tSeed;
    cout << "Seeds ---- " <<endl;
    print_formula_list(Seed);
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

void Decider::mp_closure(){
    int size = proof.stmt_list.size();
    for(int i=0; i< size;i++){
        Formula* f = proof.stmt_list[i];
        Formula* l = proof.get(f->lhs->to_string());
        if(l!=NULL) proof.push(f->rhs);//f is (L-R), L is already in proof, so push R into proof
    }
}

/**  Proof_Map **/
void Proof_Map::push(Formula* f){
    string key = f->to_string();
    if(map.find(key) == map.end()){
        int i = stmt_list.size();
        map[key] = i;
        stmt_list.push_back(f);
    }
    else{
        cout << "formula already exists in stmt list";
        f->print_line();
    }
}

Formula* Proof_Map::get(string key){
    int i;
    if(map.find(key) != map.end()){
        return stmt_list[map[key]];
    }
    else{
        //cout << "formula doesnt exist in stmt list" << endl;
        return NULL;
    }
}
