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
    SExpression * atom(SExpression * expression);
    SExpression * plus(SExpression * expression1,SExpression * expression2 );
    SExpression * minus(SExpression * expression1,SExpression * expression2 );
    SExpression * times(SExpression * expression1,SExpression * expression2 );
    SExpression * quotient(SExpression * expression1,SExpression * expression2 );
    SExpression * reminder(SExpression * expression1,SExpression * expression2 );
    SExpression * less(SExpression * expression1,SExpression * expression2 );
    SExpression * greater(SExpression * expression1,SExpression * expression2 );
    SExpression*  getValFromAlist(SExpression * symbolicAtom,SExpression * aList);
    SExpression* addPairsToAList(SExpression * parameters, SExpression * arguments, SExpression * initialAList);
    SExpression * addFunctionToDlist(SExpression * function, SExpression * initialDlist);
    SExpression * getValFromDlist(SExpression* functionName, SExpression * dlist);
    bool isInAlist(SExpression * symbolicAtom,SExpression * aList);
    bool isTrue(SExpression * exp);
public:
    SExpression * eval(SExpression * exp, SExpression * Alist, SExpression ** Dlist);
};


#endif //LISPINTERPRETER_EVALUATOR_H
