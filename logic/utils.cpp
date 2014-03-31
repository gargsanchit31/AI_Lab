#include "utils.h"
using namespace std;

/* shared variables */
Formula * TheFalse = new Formula('F');

/* functions  */
Formula* parse(){ //formula is either 'a' OR (<f> - <f>)
    Formula * formula;

    char x;
    cin >> x;
    if(x != '('){//i.e its 'a'
        if(x == 'F') {
            cout << "false is input" <<endl;
            formula = TheFalse;
        }
        else formula = new Formula(x);

        return formula;
    }

    //its (f - f)
    Formula * lhs;
    Formula * rhs;
    lhs = parse();

    cin >>x ; //for '-'
    if(x != '-'){ //Error checking
        cout << "Found character '" << x <<"'. Expected '-'" <<endl;
        return NULL;
    }

    rhs = parse();

    cin >> x; //for ')'
    if(x != ')'){ //Error checking
        cout << "Found character '" << x <<"'. Expected ')'" <<endl;
        return NULL;
    }

    formula = new Formula('-', lhs, rhs);

    return formula;
}

Formula* parse_new(){ //formula is either 'a' OR (<f> - <f>)
    Formula * formula;

    char x;
    cin >> x;
    if(x != '(' && x!='~'){//i.e its 'a'
        cout << "x is " << x << endl;

        if(x == 'F') formula = TheFalse;
        else formula = new Formula(x);

        return formula;
    }

    if(x == '~'){
        Formula * lhs;
        cout << "calling lhs on negation" << endl;
        lhs = parse_new();
        Formula * False = TheFalse;
        formula = implication(lhs, False);
        return formula;
    }

    //x is (

    //its (f - f)
    Formula * lhs;
    Formula * rhs;
    lhs = parse_new();

    char op;

    cin >>op ; //for '-'
    if(op != '-' && op!='&' && op != '|'){ //Error checking
        cout << "Found character '" << op <<"'. Expected '-', '|' or '&'" <<endl;
        return NULL;
    }

    rhs = parse_new();

    cin >> x; //for ')'
    if(x != ')'){ //Error checking
        cout << "Found character '" << x <<"'. Expected ')'" <<endl;
        return NULL;
    }
    if(op == '-'){
        formula = new Formula(op, lhs, rhs);
    }
    else if(op == '|'){
        Formula * False = TheFalse;
        formula = implication(implication(lhs, False), rhs); 
    }
    else if(op == '&'){
        Formula * False = TheFalse;
        formula = implication(implication(lhs, implication(rhs, False)), False);
    }
    return formula;
}

Formula * implication(Formula *lhs, Formula *rhs){
    Formula * formula = new Formula('-', lhs ,rhs);
    return formula;
}

Formula * Axiom1(Formula *A, Formula *B){
    return  implication(//1
                A,
                implication(B, A)//2
            );
}

void destroy_Axiom1(Formula *axiom){
    delete(axiom->rhs);//2
    delete(axiom);//1
}

Formula * Axiom2(Formula *A, Formula *B, Formula *C){
    return  implication(//1
                implication(//2
                    A, 
                    implication(B, C)//4
                ),
                implication(//3
                    implication(A, B),//5
                    implication(A, C) //6
                )
            );
}
void destroy_Axiom2(Formula *axiom){
    delete(axiom->lhs->rhs);//4
    delete(axiom->lhs);//2

    delete(axiom->rhs->lhs);//5
    delete(axiom->rhs->rhs);//6
    delete(axiom->rhs); //3

    delete(axiom); //1
}

Formula * Axiom3(Formula *A){
    Formula * F = TheFalse;
    return  implication(//1
                implication(//2
                    implication(A, F),//3
                    F
                ),
                A
            );
}

Formula * Axiom3_reverse(Formula *A){
    Formula * F = TheFalse;
    return  implication(//1
                A,
                implication(//2
                    implication(A, F),//3
                    F
                )
            );
}

void destroy_Axiom3(Formula *axiom){
    delete(axiom->lhs->lhs);//3
    delete(axiom->lhs);//2
    delete(axiom);//1
}
void destroy_Axiom3_reverse(Formula *axiom){
    delete(axiom->rhs->lhs);//3
    delete(axiom->rhs);//2
    delete(axiom);//1
}

void destroy_Formula(Formula *f){
    if(! f->is_leaf()){
        //destroy lhs and rhs recursively
        destroy_Formula(f->lhs);
        destroy_Formula(f->rhs);
    }
    delete_Formula(f);//delete self
}

void delete_Formula(Formula *f){
    //if it is TheFalse dont do anything, else delete(f)
    if(f->val == 'F'){
        if(f!=TheFalse) cout << "'F' is not TheFalse" <<endl;
        return;
    }
    delete(f);
}

bool is_axiom3_candidate(Formula* A){ //is it of the form (X-F)-F .. So don't use it for any other purpose
    if(A->is_leaf()) return false; //A is leaf
    if(A->rhs->to_string() != "F") return false; //A->rhs is not F
    if(A->lhs->is_leaf()) return false;//A->lhs is leaf
    if(A->lhs->rhs->to_string() != "F") return false;//A->lhs->rhs is not F
    return true;
}

bool isAxiom1(Formula * f){
    if(f->is_leaf()) return false;
    if(f->rhs->is_leaf()) return false;
    //check
    if( *(f->lhs) == *(f->rhs->rhs)) return true;
}

bool isAxiom3(Formula * f){
    if(f->is_leaf()) return false;
    if(f->lhs->is_leaf()) return false;
    if(f->lhs->lhs->is_leaf()) return false;
    //check
    if( *(f->rhs) == *(f->lhs->lhs->lhs)) return true;
}

bool isAxiom2(Formula * f){
    if(f->is_leaf()) return false;

    if(f->lhs->is_leaf()) return false;
    if(f->lhs->rhs->is_leaf()) return false;

    if(f->rhs->is_leaf()) return false;
    if(f->rhs->lhs->is_leaf()) return false;
    if(f->rhs->rhs->is_leaf()) return false;
    //check
    //(a1-(b1-c1)) - ((a3-b2)-(a3-c2)) to list
    Formula * a1 = f->lhs->lhs;
    Formula * a2 = f->rhs->lhs->lhs;
    Formula * a3 = f->rhs->rhs->lhs;

    Formula * b1 = f->lhs->rhs->lhs;
    Formula * b2 = f->rhs->lhs->rhs;

    Formula * c1 = f->lhs->rhs->rhs;
    Formula * c2 = f->rhs->rhs->rhs;
    if((*a1 == *a2) && (*a2 == *a3) && (*b1 == *b2) && (*c1 == *c2)) return true;
    /*
    a1->print_line();
    a2->print_line();
    a3->print_line();
    b1->print_line();
    b2->print_line();
    c1->print_line();
    c2->print_line();
    */
}
