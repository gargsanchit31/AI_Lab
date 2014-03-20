#include "decider.h"
#include <ctime>
#include <unistd.h>
#include <stack>
/** Annotation **/
void Annotation::print(){
    switch(rule){
        case Hyp:
            cout <<" .... Hypothesis" <<endl;
            break; //optional
        case MP  :
            cout <<" .... MP " << l1 << ", " << l2<<endl;
            break; //optional
        case Ax1  :
            cout <<" .... Ax1 " <<endl;
            break; //optional
        case Ax2  :
            cout <<" .... Ax2 " <<endl;
            break; //optional
        case Ax3  :
            cout <<" .... Ax3 " <<endl;
            break; //optional
        default : //Optional
            cout << " .... Corrupt Annotation. Should Not reach Here. Exiting." <<endl;
            exit(0);
    }
}

/**  Decider **/
Decider::Decider(Formula * stmt, Formula_List tSeed){
    statement = stmt;
    genererate_hypothesis(statement, hypothesis_list);
    //print_formula_list(hypothesis_list);

    Annotation ann;
    ann.rule = Hyp;
    for(int i=0; i<hypothesis_list.size(); i++){
        proof.push(hypothesis_list[i], ann);
    }
    cout << "Hypothesis list" <<endl;
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
    sleep(3);
    int x;
    int LIMIT = 5;
    for(int i=0; i<LIMIT; i++){
        mp_closure();
        if(proof.get("F") != -1){
            cout << "Proof found" << endl;
            cin >> x;
            proof.trace();
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
    Annotation ann;
    ann.rule = MP;
    int size = proof.stmt_list.size();
    for(int i=0; i< size;i++){
        Formula* f = proof.stmt_list[i];
        cout << "f is : " ; f->print();
        if(!f->is_leaf()){
            int index = proof.get(f->lhs->to_string());
            cout << " non-leaf ";
            if(index!=-1) {
                Formula* l = proof.stmt_list[index];
                cout <<"  MP applicable on rhs '";
                l->print();
                cout <<"'" <<endl;
                ann.l1 = i;//p-q
                ann.l2 = index;//p
                proof.push(f->rhs, ann);//f is (L-R), L is already in proof, so push R into proof
            }
            cout << endl;
        }
        else{
            cout << " leaf " <<endl;
        }
    }
}

void Decider::axiom1_closure(){
    Annotation ann;
    ann.rule = Ax1;
    int size_seed = Seed.size();
    int size_stmt = proof.stmt_list.size();
    for(int i=0; i<size_seed; ++i){
        Formula* A = Seed[i];
        for(int j=0;j<size_seed;++j){
            Formula* B = Seed[j];
            ann.a = A;
            ann.b = B;
            proof.push(implication(A,implication(B,A)), ann);
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            ann.a = A;
            ann.b = B;
            proof.push(implication(A,implication(B,A)), ann);
        }
    }
    for(int i=0; i<size_stmt; ++i){
        Formula* A = proof.stmt_list[i];
        for(int j=0;j<size_seed;++j){
            Formula* B = Seed[j];
            ann.a = A;
            ann.b = B;
            proof.push(implication(A,implication(B,A)), ann);
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            ann.a = A;
            ann.b = B;
            proof.push(implication(A,implication(B,A)), ann);
        }
    }
}

void Decider::axiom3_closure(){
    Annotation ann;
    int size_seed = Seed.size();
    int size_stmt = proof.stmt_list.size();
    for(int i=0; i<size_seed; ++i){
        Formula* A = Seed[i];
        Formula* F = new Formula('F');
        ann.a = A;
        proof.push(implication(implication(implication(A, F), F), A), ann);
    }
    for(int i=0; i<size_stmt; ++i){
        Formula* A = proof.stmt_list[i];
        Formula* F = new Formula('F');
        ann.a = A;
        proof.push(implication(implication(implication(A, F), F), A), ann);
    }
}

/**  Proof_Map **/
void Proof_Map::push(Formula* f, Annotation ann){
    string key = f->to_string();
    if(map.find(key) == map.end()){
        int i = stmt_list.size();
        map[key] = i;
        stmt_list.push_back(f);
        ann_list.push_back(ann);
    }
    else{
        cout << "formula already exists in stmt list : ";
        f->print_line();
    }
}

int Proof_Map::get(string key){
    if(map.find(key) != map.end()){
        return map[key];
    }
    else{
        return -1;
    }
}

void Proof_Map::print(int i){
    cout << "L"<< i << ": ";
    stmt_list[i]->print();
    ann_list[i].print();
}

void Proof_Map::print(){
    for(int i=0;i< stmt_list.size(); i++){
        print(i);
    }
}

void Proof_Map::trace(){
    vector<bool> &V = *new vector<bool>(stmt_list.size(), false);
    stack<int> path;
    cout << "no of proof steps scanned : " << V.size() <<endl;
    int end = get("F");
    path.push(end);
    while(path.size() !=0){
        int i =  path.top();
        path.pop();
        V[i] = true;
        Annotation ann= ann_list[i];
        if(ann.rule == MP){
            path.push(ann.l1);
            path.push(ann.l2);
        }
    }

    cout << "'F' -- found @ index " << end <<endl;

    cout << "Proof Steps : " << endl;
    for(int i=0;i <V.size();i++){
        if(V[i]) {
            print(i);
        }
    }
}