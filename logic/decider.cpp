#include "decider.h"
#include <ctime>
#include <unistd.h>
#include <stack>

int length_limit;
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
        Formula* hyp = implication(stmt, TheFalse);
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
    int LIMIT = 10;
    length_limit = 10;
    for(int i=0; i<LIMIT; i++){
        cout << "round " << i;
        cout << "length_limit " << length_limit <<endl;
        cout << "proof size " << proof.stmt_list.size() <<endl;
        mp_closure();
        if(proof.get("F") != -1){
            cout << "Proof found" << endl;
            cin >> x;
            proof.trace();
            return;
        }
        axiom1_closure();
        cout << "ax 1" <<endl;
        cout << "proof size " << proof.stmt_list.size() <<endl;
        axiom2_closure();
        cout << "ax 2" <<endl;
        cout << "proof size " << proof.stmt_list.size() <<endl;
        axiom3_closure();
        cout << "ax 3" <<endl;
        cout << "proof size " << proof.stmt_list.size() <<endl;

        length_limit+=3; //twice the length limit

        //print_formula_list(proof.stmt_list);
        //cout << "continue enter any number to continue? ";
        //cin >> x;
    }
    cout << "Could Not prove" <<endl;
}

void Decider::mp_closure(){
    Annotation ann;
    ann.rule = MP;
    int delta; //keep track of additions in each round of MP closure
    do{
        delta = 0;
        int size = proof.stmt_list.size();
        for(int i=0; i< size;i++){
            Formula* f = proof.stmt_list[i];
            //cout << "f is : " ; f->print();
            if(!f->is_leaf()){
                int index = proof.get(f->lhs->to_string());
                //cout << " non-leaf ";
                if(index!=-1) {
                    Formula* l = proof.stmt_list[index];
                    //cout <<"  MP applicable on rhs '";
                    //l->print();
                    //cout <<"'" <<endl;
                    ann.l1 = i;//p-q
                    ann.l2 = index;//p
                    int status = proof.push(f->rhs, ann);//f is (L-R), L is already in proof, so push R into proof
                    if(status == 0) delta++; //increment only if push added a new formula in proof
                }
                //cout << endl;
            }
            else{
                //cout << " leaf " <<endl;
            }
        }
    }
    while(delta > 0);
}

void Decider::mp_closure_onepass(){
    Annotation ann;
    ann.rule = MP;
    int size = proof.stmt_list.size();
    for(int i=0; i< size;i++){
        Formula* f = proof.stmt_list[i];
        //cout << "f is : " ; f->print();
        if(!f->is_leaf()){
            int index = proof.get(f->lhs->to_string());
            //cout << " non-leaf ";
            if(index!=-1) {
                Formula* l = proof.stmt_list[index];
                //cout <<"  MP applicable on rhs '";
                //l->print();
                //cout <<"'" <<endl;
                ann.l1 = i;//p-q
                ann.l2 = index;//p
                proof.push(f->rhs, ann);//f is (L-R), L is already in proof, so push R into proof
            }
            //cout << endl;
        }
        else{
            //cout << " leaf " <<endl;
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
            Formula* f =Axiom1(A,B); 
            if(f->len <= length_limit) proof.push(f,ann);
            else {
                delete f;
            }
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            ann.a = A;
            ann.b = B;
            Formula* f =Axiom1(A,B); 
            if(f->len <= length_limit) proof.push(f,ann);
            else {
                delete f;
            }
        }
    }
    for(int i=0; i<size_stmt; ++i){
        Formula* A = proof.stmt_list[i];
        for(int j=0;j<size_seed;++j){
            Formula* B = Seed[j];
            ann.a = A;
            ann.b = B;
            Formula* f =Axiom1(A,B); 
            if(f->len <= length_limit) proof.push(f,ann);
            else {
                delete f;
            }
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            ann.a = A;
            ann.b = B;
            Formula* f =Axiom1(A,B); 
            if(f->len <= length_limit) proof.push(f,ann);
            else {
                delete f;
            }
        }
    }
}

void Decider::axiom2_closure(){
    Annotation ann;
    ann.rule = Ax2;
    int size[2] = {(int)(Seed.size()),(int)(proof.stmt_list.size())};
    Formula_List* flist[2] = {&Seed,&(proof.stmt_list)};

    int count=0;
    for(;count<8;++count){
        int b1 = (count&1 ==1);
        int b2 = (count&2 ==2);
        int b3 = (count&4 ==4);
        Formula_List &fl1 = (*flist[b1]);
        Formula_List &fl2 = (*flist[b2]);
        Formula_List &fl3 = (*flist[b3]);
        for(int i=0;i<size[b1];++i){
            Formula* A = fl1[i];
            for(int j=0;j<size[b2];++j){
                Formula* B = fl2[j];
                for(int k=0;k<size[b3];++k){
                    Formula* C = fl3[k];
                    ann.a = A;
                    ann.b = B;
                    ann.c = C;
                    Formula* f =Axiom2(A,B,C);
                    if(f->len <= length_limit) proof.push(f,ann);
                    else delete f;
                }
            }
        }
    }
}

void Decider::axiom3_closure(){
    Annotation ann;
    ann.rule = Ax3;
    int delta;
    do{
        delta = 0;
        int size_stmt = proof.stmt_list.size();
        for(int i=0; i<size_stmt; ++i){
            Formula* A = proof.stmt_list[i];
            //if A is of the form ((p-F)-F) apply axiom 3 with p as param
            if(A->is_leaf()) continue; //A is leaf
            if(A->rhs->to_string() != "F") continue; //A->rhs is not F
            if(A->lhs->is_leaf()) continue;//A->lhs is leaf
            if(A->lhs->rhs->to_string() != "F") continue;//A->lhs->rhs is not F

            //A is not leaf, its rhs is "F", its lhs is not leaf, its lhs->rhs is "F"
            //i.e A is ((p-F)-F)
            Formula* P = A->lhs->lhs;

            ann.a = P;
            int status = proof.push(Axiom3(P), ann); //((p-F)-F) - p

            if(status == 0) delta++;
        }
    }
    while(delta > 0);
}

void Decider::axiom3_closure_brute(){
    Annotation ann;
    ann.rule = Ax3;
    int size_seed = Seed.size();
    int size_stmt = proof.stmt_list.size();
    for(int i=0; i<size_seed; ++i){
        Formula* A = Seed[i];
        ann.a = A;
        proof.push(Axiom3(A), ann);
    }
    for(int i=0; i<size_stmt; ++i){
        Formula* A = proof.stmt_list[i];
        ann.a = A;
        proof.push(Axiom3(A), ann);
    }
}

/**  Proof_Map **/
int Proof_Map::push(Formula* f, Annotation ann){
    string key = f->to_string();
    if(map.find(key) == map.end()){
        int i = stmt_list.size();
        map[key] = i;
        stmt_list.push_back(f);
        ann_list.push_back(ann);
        return 0;
    }
    else{
        //cout << "formula already exists in stmt list : ";
        //f->print_line();
        return -1;
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
