#ifndef _UTILS_H
#define _UTILS_H
#include "formula.h"

extern Formula* TheFalse;

/* shared variables */

/* functions  */

Formula* parse();
Formula* parse_new(); // allows ~ symbol
    
Formula * implication(Formula *lhs, Formula *rhs);

Formula * Axiom1(Formula *A, Formula *B);
Formula * Axiom2(Formula *A, Formula *B, Formula *C);
Formula * Axiom3(Formula *A);
void destroy_Axiom1(Formula *axiom);
void destroy_Axiom2(Formula *axiom);
void destroy_Axiom3(Formula *axiom);
void destroy_Formula(Formula *f);


#endif
