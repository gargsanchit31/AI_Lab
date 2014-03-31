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
Formula * Axiom3_reverse(Formula *A);

bool isAxiom1(Formula * f);
bool isAxiom2(Formula * f);
bool isAxiom3(Formula * f);

void destroy_Axiom1(Formula *axiom);
void destroy_Axiom2(Formula *axiom);
void destroy_Axiom3(Formula *axiom);
void destroy_Axiom3_reverse(Formula *axiom);
void destroy_Formula(Formula *f);
void delete_Formula(Formula *f); //if it is TheFalse dont do anything, else delete(f)

bool is_axiom3_candidate(Formula* f); //is it of the form (A-F)-F .. So don't use it for any other purpose
bool is_a_imp_f(Formula* f); //is it of the form (A-F)

#endif
