#ifndef _UTILS_H
#define _UTILS_H
#include "formula.h"

/* shared variables */

/* functions  */

Formula* parse();
Formula* parse_new(); // allows ~ symbol
    
Formula * implication(Formula *lhs, Formula *rhs);

Formula * Axiom1(Formula *A, Formula *B);
Formula * Axiom2(Formula *A, Formula *B, Formula *C);
Formula * Axiom3(Formula *A);


#endif
