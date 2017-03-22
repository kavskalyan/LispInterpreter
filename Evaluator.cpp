//
// Created by Kalyan Khandrika on 3/21/17.
//

#include "Evaluator.h"
SExpression * Evaluator::evCon(SExpression * be, SExpression * Alist, SExpression * Dlist){
    if(null(be)){
        return NULL;
    }
    else if(eval(car(car(be)),Alist,Dlist) == SExpression::symbolicAtom("T")){
            SExpression * cadarBE = car(cdr(car(be)));
            return eval(cadarBE,Alist,Dlist);
    } else{
        return evCon(cdr(be),Alist,Dlist);
    }
}
SExpression * Evaluator::evLis(SExpression * list, SExpression * Alist, SExpression * Dlist){
    if(null(list)){
        return NULL;
    }
    else{
        return cons(eval(car(list),Alist,Dlist),evLis(cdr(list),Alist,Dlist));
    }
}
SExpression * Evaluator::apply(SExpression * function,SExpression * arguments, SExpression * Alist, SExpression * Dlist){

}
SExpression * Evaluator::eval(SExpression * exp, SExpression * Alist, SExpression * Dlist){
//    if(exp->getType() != NONATOM){
//        if(isInt(exp)) return exp;
//        else if()
//    }
    return NULL;
}
SExpression * Evaluator::car(SExpression * expression){
    if(expression->getType()== NONATOM)
        return expression->getLeft();
    else
        throw std::runtime_error("**error: primitive CAR function called on atomic s-expression");
    return NULL;
}
SExpression * Evaluator::cdr(SExpression * expression){
    if(expression->getType()== NONATOM)
        return expression->getRight();
    else
        throw std::runtime_error("**error: primitive CDR function called on atomic s-expression");
    return NULL;
}
SExpression * Evaluator::cons(SExpression * expression1,SExpression * expression2 ){
    SExpression * newExpression = new SExpression(NONATOM);
    newExpression->setLeft(expression1);
    newExpression->setRight(expression2);
    return newExpression;
}
SExpression * Evaluator::eq(SExpression * expression1,SExpression * expression2 ){
    SExpression * returnExp = NULL;
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        returnExp = expression1->getVal() == expression2->getVal()?  SExpression::symbolicAtom("T") :  SExpression::symbolicAtom("Nil");
    }
    else if(expression1->getType() == SYMBOLICATOM && expression2->getType() == SYMBOLICATOM){
        returnExp = expression1->getName() == expression2->getName()?  SExpression::symbolicAtom("T") :  SExpression::symbolicAtom("Nil");
    }
    else
        throw std::runtime_error("**error: primitive EQ function called on non-atomic s-expressions / invalid s-expressions");
    return returnExp;
}
SExpression * Evaluator::null(SExpression * expression){
    return expression == SExpression::symbolicAtom("Nil")? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("Nil");
}
SExpression * Evaluator::isInt(SExpression * expression){
    return expression->getType() == INTEGERATOM? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("Nil");
}
SExpression * Evaluator::plus(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal()+expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error("**error: Types mismatch in primitive function PLUS. Called on non-atomic s-expressions / invalid s-expressions");

}
SExpression * Evaluator::times(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal() * expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error("**error: Types mismatch in primitive function TIMES. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::quotient(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal()/expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error("**error: Types mismatch in primitive function QUOTIENT. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::remainder(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal() % expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error("**error: Types mismatch in primitive function REMAINDER. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::less(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()<expression2->getVal()? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("Nil");
    }
    throw std::runtime_error("**error: Types mismatch in primitive function LESS. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::greater(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()>expression2->getVal()? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("Nil");
    }
    throw std::runtime_error("**error: Types mismatch in primitive function GREATER. Called on non-atomic s-expressions / invalid s-expressions");
}
