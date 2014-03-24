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
        formula = new Formula(x);
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
        formula = new Formula(x);
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
void destroy_Axiom3(Formula *axiom){
    delete(axiom->lhs->lhs);//3
    delete(axiom->lhs);//2
    delete(axiom);//1
}
