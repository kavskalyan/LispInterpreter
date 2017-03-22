//
// Created by Kalyan Khandrika on 3/21/17.
//

#ifndef LISPINTERPRETER_EVALUATOR_H
#define LISPINTERPRETER_EVALUATOR_H

#include "SExpression.h"
//CAR, CDR, CONS, ATOM, EQ, NULL, INT,
//PLUS, MINUS, TIMES, QUOTIENT, REMAINDER, LESS, GREATER
//        COND, QUOTE, DEFUN
class Evaluator {
    SExpression * evCon(SExpression * be, SExpression * Alist, SExpression * Dlist);
    SExpression * evLis(SExpression * be, SExpression * Alist, SExpression * Dlist);
    SExpression * apply(SExpression * function,SExpression * arguments, SExpression * Alist, SExpression * Dlist);
    SExpression * car(SExpression * expression);
    SExpression * cdr(SExpression * expression);
    SExpression * cons(SExpression * expression1,SExpression * expression2 );
    SExpression * eq(SExpression * expression1,SExpression * expression2 );
    SExpression * null(SExpression * expression);
    SExpression * isInt(SExpression * expression);
    SExpression * plus(SExpression * expression1,SExpression * expression2 );
    SExpression * times(SExpression * expression1,SExpression * expression2 );
    SExpression * quotient(SExpression * expression1,SExpression * expression2 );
    SExpression * remainder(SExpression * expression1,SExpression * expression2 );
    SExpression * less(SExpression * expression1,SExpression * expression2 );
    SExpression * greater(SExpression * expression1,SExpression * expression2 );

public:
    SExpression * eval(SExpression * exp, SExpression * Alist, SExpression * Dlist);
};


#endif //LISPINTERPRETER_EVALUATOR_H
