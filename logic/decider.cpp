#include "decider.h"
#include <ctime>
#include <unistd.h>

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
        if(stmt->val == 'F') return; //do nothing, were done
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

void Decider::prove(){
    cout << "hello" <<endl;
    sleep(10);
    int x;
    int LIMIT = 5;
    for(int i=0; i<LIMIT; i++){
        mp_closure();
        if(proof.get("F") != NULL){
            cout << "Proof found" << endl;
            cin >> x;
            print_formula_list(proof.stmt_list);
            return;
        }
        axiom1_closure();
        print_formula_list(proof.stmt_list);
        axiom3_closure();
        //cout << "continue enter any number to continue? ";
        //cin >> x;
    }
    cout << "Could Not prove" <<endl;
}

void Decider::mp_closure(){
    int size = proof.stmt_list.size();
    for(int i=0; i< size;i++){
        Formula* f = proof.stmt_list[i];
        cout << "f is : " ; f->print();
        if(!f->is_leaf()){
            Formula* l = proof.get(f->lhs->to_string());
            cout << " non-leaf ";
            if(l!=NULL) {
                cout <<"  MP applicable on rhs '";
                l->print();
                cout <<"'" <<endl;
                proof.push(f->rhs);//f is (L-R), L is already in proof, so push R into proof
            }
            cout << endl;
        }
        else{
            cout << " leaf " <<endl;
        }
    }
}

void Decider::axiom1_closure(){
    int size_seed = Seed.size();
    int size_stmt = proof.stmt_list.size();
    for(int i=0; i<size_seed; ++i){
        Formula* A = Seed[i];
        for(int j=0;j<size_seed;++j){
            Formula* B = Seed[j];
            proof.push(implication(A,implication(B,A)));
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            proof.push(implication(A,implication(B,A)));
        }
    }
    for(int i=0; i<size_stmt; ++i){
        Formula* A = proof.stmt_list[i];
        for(int j=0;j<size_seed;++j){
            Formula* B = Seed[j];
            proof.push(implication(A,implication(B,A)));
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            proof.push(implication(A,implication(B,A)));
        }
    }
}

void Decider::axiom3_closure(){
    int size_seed = Seed.size();
    int size_stmt = proof.stmt_list.size();
    for(int i=0; i<size_seed; ++i){
        Formula* A = Seed[i];
        Formula* F = new Formula('F');
        proof.push(implication(implication(implication(A, F), F), A));
    }
    for(int i=0; i<size_stmt; ++i){
        Formula* A = proof.stmt_list[i];
        Formula* F = new Formula('F');
        proof.push(implication(implication(implication(A, F), F), A));
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
        cout << "formula already exists in stmt list : ";
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
