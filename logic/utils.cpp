#include "utils.h"
using namespace std;

/* shared variables */

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

Formula * implication(Formula *lhs, Formula *rhs){
    Formula * formula = new Formula('-', lhs ,rhs);
    return formula;
}

Formula * Axiom1(Formula *A, Formula *B){
    return implication(A, implication(B, A));
}

Formula * Axiom2(Formula *A, Formula *B, Formula *C){
    return  implication(
                implication(
                    A, 
                    implication(B, C)
                ),
                implication(
                    implication(A, B),
                    implication(A, C)
                )
            );
}

Formula * Axiom3(Formula *A){
    Formula * F = new Formula('F');
    return  implication(
                implication(
                    implication(A, F),
                    F
                ),
                A
            );
}
