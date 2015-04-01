#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    float coeff;
    int degree;
}   Monomial;

typedef struct ElemOfPolynomial
{
    Monomial m;
    struct ElemOfPolynomial *next;
    struct ElemOfPolynomial *prev;
}   ElemOfPolynomial;

typedef struct
{
    int numberMonomials;
    int higherDegree;
    ElemOfPolynomial *head;
    ElemOfPolynomial *tail;
}   Polynomial;

Monomial createMonomial(float new_coeff,int new_x);
Polynomial createPolynomial(char *filepath);
Polynomial addMonomial(Polynomial l,Monomial new_m);
Polynomial removeMonomial(Polynomial l,int taken_degree);
Polynomial sum(Polynomial l1,Polynomial l2);
Polynomial sub(Polynomial l1,Polynomial l2);
Polynomial mul(Polynomial l1,Polynomial l2);
Polynomial divP(Polynomial l1,Polynomial l2);
Polynomial mDerivative(Monomial m,int n);
Polynomial pDerivative(Polynomial l,int n);
Polynomial gcd(Polynomial l1,Polynomial l2);
void printMonomial(Monomial m);
void printPolynomial(Polynomial l);

Polynomial init(Polynomial l);
Polynomial derivatePolynomial(Polynomial l);
Polynomial copyPolynomial(Polynomial l);
Polynomial remainder(Polynomial l1,Polynomial l2);
int sizeint(int nb);
int pow10(int p);

#endif
