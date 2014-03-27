#include "decider.h"
#include <ctime>
#include <unistd.h>
#include <stack>

int length_limit;
/** Annotation **/
Annotation::Annotation(){
    flag_ax2_e = false;
    flag_ax2_sp = false;
}
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
Decider::~Decider(){
    cout << "Destroying decider" <<endl;
    int i;

    //statement to prove
    delete(statement);  //only delete this, as its parts are in hypothesis list(or later proof);

    //proof steps
    Formula_List & L = proof.stmt_list;
    Annotation_List & A = proof.ann_list;
    for(i=L.size()-1; i>=0;i--){ //IMPORTANT NOTE: delte from reverse as later-ones depend on previous ones
        switch(A[i].rule){
            case Hyp: //if its hypothesis, destroy_Formula
                destroy_Formula(L[i]);
                break;
            case Ax1:
                destroy_Axiom1(L[i]);
                break;
            case Ax2:
                destroy_Axiom2(L[i]);
                break;
            case Ax3:
                destroy_Axiom3(L[i]);
                break;
            case MP://just 'delete' it
                delete_Formula(L[i]); //if val is 'F' don't delete it(TheFalse)
                break;
        }
    }

    //hypothesis list  deletion NOT NEEDED AS ALL hypothesis are also in proof

    //Seed
    for(i=0; i<Seed.size();i++){ //destroy_Formula  as its components are nowhere else
        destroy_Formula(Seed[i]);
    }

    //delete TheFalse at the end
    delete(TheFalse);
}

Decider::Decider(Formula * stmt, Formula_List tSeed){
    statement = stmt;
    genererate_hypothesis(statement, hypothesis_list);
    //print_formula_list(hypothesis_list);

    Annotation ann;
    ann.rule = Hyp;
    for(int i=0; i<hypothesis_list.size(); i++){
        int status = proof.push(hypothesis_list[i], ann);
        if(status == -1){ //delete hypothesis i.e destroy_Formula
            destroy_Formula(hypothesis_list[i]);
        }
    }
    //Don't use hypothesis list after this, it may become invalid because push(hyp[i]) may delete hyp[i] if repeated
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
    sleep(1);
    int x;
    int LIMIT = 20;
    length_limit = 5;
    int size_before, size_after;
    for(int i=0; i<LIMIT; i++){
        size_before = proof.stmt_list.size();
        cout << "Round " << i <<" Length_limit " << length_limit << " Proof Size=" << proof.stmt_list.size() <<endl;
        mp_closure();
        if(proof.get("F") != -1){
            cout << "Proof found" << endl;
            cin >> x;
            proof.trace();
            return;
        }
        axiom1_closure();
        cout << "ax 1: " << proof.stmt_list.size() <<endl;
        axiom2_closure_expansion();
        cout << "ax 2: Expansion" << proof.stmt_list.size() <<endl;
        axiom2_closure_reduction();
        cout << "ax 2: Reduction" << proof.stmt_list.size() <<endl;
        axiom2_closure_special();
        cout << "ax 2: Special" << proof.stmt_list.size() <<endl;
        axiom3_closure();
        cout << "ax 3: " << proof.stmt_list.size() <<endl;

        size_after = proof.stmt_list.size();
        if(size_after == size_before){//i.e no progress in this round
            cout << "-------  Incrementing the limit" << endl;
            length_limit+=1; //twice the length limit
        }
        else{
            i--; //Preserving the round count in next round
            cout << "-------  Keeping the Same limit" << endl;
        }

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
                    //Formula* l = proof.stmt_list[index];
                    //cout <<"  MP applicable on rhs '";
                    //l->print();
                    //cout <<"'" <<endl;
                    ann.l1 = i;//p-q
                    ann.l2 = index;//p
                    Formula * newstep = f->rhs;
                    Formula * copy = newstep->copy();
                    int status = proof.push(copy, ann);//f is (L-R), L is already in proof, so push R into proof
                    if(status == -1){
                        delete_Formula(copy);
                    }
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

void Decider::mp_closure_onepass(){//Not Used
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
                //Formula* l = proof.stmt_list[index];
                //cout <<"  MP applicable on rhs '";
                //l->print();
                //cout <<"'" <<endl;
                ann.l1 = i;//p-q
                ann.l2 = index;//p
                Formula * copy = f->rhs->copy();
                int status = proof.push(copy, ann);//f is (L-R), L is already in proof, so push R into proof
                if(status == -1){
                    delete_Formula(copy);
                }
            }
            //cout << endl;
        }
        else{
            //cout << " leaf " <<endl;
        }
    }
}

void Decider::axiom1_closure(){
//* if some "lhs" is of the form (B-A) i.e is not a leaf add axiom1 :  A-(B-A)
    //length_limit = 20;
    Annotation ann;
    ann.rule = Ax1;
    int size_stmt = proof.stmt_list.size();
    Formula_List & FL = proof.stmt_list;
    for(int i=0;i<size_stmt;i++){
        Formula * stmt = FL[i];
        if(is_axiom3_candidate(stmt)){
            //cout<<"ax 3 candidate" <<endl;
            continue;
        } //WATCH its axiom3 candidate. Don't consider
        if(stmt->is_leaf()) continue;
        if(stmt->lhs->is_leaf()) continue;
        //cout << "come here " <<endl;
        //i.e stmt has lhs which is not leaf . So apply Axiom1
        Formula * B = stmt->lhs->lhs;
        Formula * A = stmt->lhs->rhs;
        ann.a = A;
        ann.b = B;
        Formula* f =Axiom1(A,B); 
//        f->print_line();
        if(f->len <= length_limit){
            int status = proof.push(f,ann);
            if(status == -1){
                destroy_Axiom1(f);
            }
        }
        else {
            destroy_Axiom1(f);
        }
    }
}

void Decider::axiom1_closure_brute(){
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
            if(f->len <= length_limit){
                int status = proof.push(f,ann);
                if(status == -1){
                    destroy_Axiom1(f);
                }
            }
            else {
                destroy_Axiom1(f);
            }
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            ann.a = A;
            ann.b = B;
            Formula* f =Axiom1(A,B); 
            if(f->len <= length_limit){
                int status = proof.push(f,ann);
                if(status == -1){
                    destroy_Axiom1(f);
                }
            }
            else {
                destroy_Axiom1(f);
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
            if(f->len <= length_limit){
                int status = proof.push(f,ann);
                if(status == -1){
                    destroy_Axiom1(f);
                }
            }
            else {
                destroy_Axiom1(f);
            }
        }
        for(int j=0;j<size_stmt;++j){
            Formula* B = proof.stmt_list[j];
            ann.a = A;
            ann.b = B;
            Formula* f =Axiom1(A,B); 
            if(f->len <= length_limit){
                int status = proof.push(f,ann);
                if(status == -1){
                    destroy_Axiom1(f);
                }
            }
            else {
                destroy_Axiom1(f);
            }
        }
    }
}

void Decider::axiom2_closure_expansion(){
//* if whole line is of form  (A-(B-C)):  expand it using axiom2 
    Annotation ann;
    ann.rule = Ax2;
    int size_stmt = proof.stmt_list.size();
    Formula_List & FL = proof.stmt_list;
    Annotation_List & AL = proof.ann_list;
    for(int i=0;i<size_stmt;i++){
        Formula * stmt = FL[i];
        Annotation ann_stmt = AL[i];
        if(ann_stmt.flag_ax2_e == true){
            //cout << "saved ax2 expansion" << endl;
            continue;
        }
        if(is_axiom3_candidate(stmt)){
            //cout<<"ax 3 candidate" <<endl;
            continue;
        } //WATCH its axiom3 candidate. Don't consider
        if(stmt->is_leaf()) continue;
        if(stmt->rhs->is_leaf()) continue;
        //it is indeed of for (A-(B-C))
        Formula * A = stmt->lhs;
        Formula * B = stmt->rhs->lhs;
        Formula * C = stmt->rhs->rhs;
        ann.a = A;
        ann.b = B;
        ann.c = C;
        ann.flag_ax2_e = true;
        Formula* f =Axiom2(A,B,C); 
//        f->print_line();
        if(f->len <= length_limit){
            int status = proof.push(f,ann);
            if(status == -1){
                destroy_Axiom2(f);
            }
        }
        else {
            destroy_Axiom2(f);
        }
    }
}

void Decider::axiom2_closure_reduction(){
//* if some "lhs" is of the form (A-B)-(A-C): treat it as rhs of axiom2
    Annotation ann;
    ann.rule = Ax2;
    int size_stmt = proof.stmt_list.size();
    Formula_List & FL = proof.stmt_list;
    for(int i=0;i<size_stmt;i++){
        Formula * line = FL[i];
        if(is_axiom3_candidate(line)){
            //cout<<"ax 3 candidate" <<endl;
            continue;
        } //WATCH its axiom3 candidate. Don't consider
        if(line->is_leaf()) continue;

        Formula *stmt = line->lhs;
        if(stmt->is_leaf()) continue;
        if(stmt->rhs->is_leaf()) continue;
        if(stmt->lhs->is_leaf()) continue;
        if(stmt->lhs->lhs->to_string() != stmt->rhs->lhs->to_string()) continue;//lhs->lhs != rhs->lhs (A1 != A2)

        Formula * A = stmt->lhs->lhs;
        Formula * B = stmt->lhs->rhs;
        Formula * C = stmt->rhs->rhs;
        ann.a = A;
        ann.b = B;
        ann.c = C;
        Formula* f =Axiom2(A,B,C); 
//        f->print_line();
        if(f->len <= length_limit){
            int status = proof.push(f,ann);
            if(status == -1){
                destroy_Axiom2(f);
            }
        }
        else {
            destroy_Axiom2(f);
        }
    }
}

void Decider::axiom2_closure_special(){
//* if some "lhs" is of the form (A-F), we can't use axiom1
//* So use axiom2, but now treat   (A-F) as 
//* (A-C) term in (A-(B-C)) - ((A-B)-(A-C))
//* We have freedom to choose B
    
    static int last_proof_size = 0; //initially 0, set @end of the function
    Annotation ann;
    ann.rule = Ax2;
    int size_stmt = proof.stmt_list.size();
    Formula_List & FL = proof.stmt_list;

    int temp_saved_count = 0;
    int temp_total_count = 0;

    int size[2] = {(int)(Seed.size()),(int)(proof.stmt_list.size())};
    Formula_List* flist[2] = {&Seed,&(proof.stmt_list)};

    for(int index=0;index<size_stmt;index++){
        Formula * line = FL[index];
        if(line->is_leaf()) continue;

        Formula *stmt = line->lhs;
        if(is_axiom3_candidate(stmt)){
            //cout<<"ax 3 candidate" <<endl;
            continue;
        } //WATCH its axiom3 candidate. Don't consider
        if(stmt->is_leaf()) continue;
        if(stmt->rhs->val != 'F') continue; //lhs is not (A-F) form

        Formula * A = stmt->lhs;
        Formula * B; //variable choose from Seed or proof_list
        Formula * C = stmt->rhs; //TheFalse

        //Note Since Axiom2(A,B,C) = (A-(B-C)) - ((A-B)-(A-C))  
        //will be atleast size >= 3a+2c+2b 
        //=>              size >= 3a+2c+2  (Unknown B will be atleast size 1)
        //So if 3a+2c >= length_limit, Better Not go into the following loop
        int estimated_length = 3*(A->len) + 2*(C->len) + 2;
        temp_total_count++;
        //cout << "estimated lenght" << estimated_length << "/ " <<length_limit << " of " << stmt->to_string() <<endl;
        if(estimated_length > length_limit){
            temp_saved_count++;
            //cout << "hurray saved " << proof.stmt_list.size() <<" operations" <<endl;
            continue;
        }

        for(int selector=0; selector<2; selector++){
            int i = 0;
            //if(i < last_proof_size && selector == 1) i=last_proof_size; //consider only new statements as candidates for B
            Formula_List &fl = *flist[selector];
            for(i=0;i<size[selector];++i){
                Formula * B = fl[i];
                ann.a = A;
                ann.b = B;
                ann.c = C;
                Formula* f = Axiom2(A,B,C);
                if(f->len <= length_limit){
                    int status = proof.push(f,ann);
                    if(status == -1){
                        destroy_Axiom2(f);
                    }
                }
                else {
                    destroy_Axiom2(f);
                }
            }
        }
    }
    last_proof_size = size_stmt; //size of proof when function was called
    cout << "temp saved fraction due to length checking = " << ((float)temp_saved_count/temp_total_count) << endl;;
}

void Decider::axiom2_closure_brute(){
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
                    Formula* f = Axiom2(A,B,C);
                    if(f->len <= length_limit){
                        int status = proof.push(f,ann);
                        if(status == -1){
                            destroy_Axiom2(f);
                        }
                    }
                    else {
                        destroy_Axiom2(f);
                    }
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
            if(!is_axiom3_candidate(A)) continue;

            //i.e A is ((p-F)-F)
            Formula* P = A->lhs->lhs;

            Formula * f = Axiom3(P);
            ann.a = P;
            int status = proof.push(f, ann); //((p-F)-F) - p
            if(status == -1){
                destroy_Axiom3(f);
            }

            if(status == 0) delta++;
        }
    }
    while(delta > 0);
}

void Decider::axiom3_closure_brute(){ //DoNot use this
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
        //handle deleting outside
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
    //cleaning all malloced stuff Vector
    delete(&V);
}
