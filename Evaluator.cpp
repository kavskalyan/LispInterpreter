//
// Created by Kalyan Khandrika on 3/21/17.
//

#include <iostream>
#include "Evaluator.h"
#define CTRUE SExpression::symbolicAtom("T")
#define  CFALSE SExpression::symbolicAtom("NIL")
SExpression * Evaluator::evCon(SExpression * be, SExpression * Alist, SExpression * Dlist){
    if(null(be) == CTRUE){
        return NULL;//error
    }
    else if(eval(car(car(be)),Alist,&Dlist) != SExpression::symbolicAtom("NIL")){
            SExpression * cadarBE = car(cdr(car(be)));
            return eval(cadarBE,Alist,&Dlist);
    } else{
        return evCon(cdr(be),Alist,Dlist);
    }
}
SExpression * Evaluator::evLis(SExpression * list, SExpression * Alist, SExpression * Dlist){
    if(null(list) == CTRUE){
        return SExpression::symbolicAtom("NIL");
    }
    else{
        return cons(eval(car(list),Alist,&Dlist),evLis(cdr(list),Alist,Dlist));
    }
}
/*
 * apply[ f, x, aList, dList] =
	[	atom[f] 	-->	[	eq[f, CAR]		-->	caar[x];		// why?
										|	eq[f, CDR]		-->	cdar[x];
										|	eq[f, CONS]	-->	cons[car[x], cdr[x]]; //??
										|	eq[f, ATOM]	-->	atom[car[x]];
										|	eq[f, NULL]	-->	null[car[x]];
										|	eq[f, EQ]			-->	eq[car[x], cadr[x]];
										|	T		-->	eval[ cdr[getval[f, dList]],
														addpairs[car[getval[f, dList]], x, aList],
														dList 			] ;		];
	|	T					-->	"error!";  ]

Elements on dList of form:  (f . (pList . body) )
addpairs[pList,x,aList]: returns new a-list

 */
SExpression * Evaluator::apply(SExpression * function,SExpression * arguments, SExpression * Alist, SExpression * Dlist){
    SExpression * returnVal = NULL;
    if(function->getType() != NONATOM) {
        if (eq(function, SExpression::symbolicAtom("CAR")) == CTRUE) {
            returnVal = car(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("CDR")) == CTRUE) {
            returnVal = cdr(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("CONS")) == CTRUE) {
            returnVal =  cons(car(arguments),car(cdr(arguments))); //???
        } else if (eq(function, SExpression::symbolicAtom("NULL")) == CTRUE) {
            returnVal = null(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("EQ")) == CTRUE) {
            returnVal = eq(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("ATOM")) == CTRUE) {
            returnVal = atom(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("INT")) == CTRUE) {
            returnVal = isInt(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("GREATER")) == CTRUE) {
            returnVal = greater(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("LESS")) == CTRUE) {
            returnVal = less(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("PLUS")) == CTRUE) {
            returnVal = plus(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("MINUS")) == CTRUE) {
            returnVal = minus(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("TIMES")) == CTRUE) {
            returnVal = times(car(arguments), car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("QUOTIENT")) == CTRUE) {
            returnVal = quotient(car(arguments), car(cdr(arguments)));
        }else if (eq(function, SExpression::symbolicAtom("REMINDER")) == CTRUE) {
            returnVal = reminder(car(arguments), car(cdr(arguments)));
        }else{
            returnVal = eval(cdr(getValFromDlist(function,Dlist)),addPairsToAList(car(getValFromDlist(function,Dlist)),arguments,Alist),&Dlist);
        }
    }
    else{
        throw std::runtime_error(">Error:: Invalid: Non atom in car of apply");
        return NULL;
    }
    if(returnVal == NULL){
        std::cout<<"FISHY"<<std::endl;
    }
    return returnVal;
}
/*
 * eval[ exp, aList, dList] =
	[	atom[exp] 	-->	[	int[exp]				-->	exp
												|	eq[exp,T]			-->	T
												|	eq[exp,NIL]	-->	NIL
												|	in[exp,aList]	-->	getVal[exp,aList]
												|	T								--> "unbound variable!"  ]
	|	atom[car[exp]] -->
					[	eq[car[exp],QUOTE] 	--> cadr[exp]
					|	eq[car[exp],COND] 	--> evcon[cdr[exp], aList, dList]
					|	eq[car[exp],DEFUN] 	--> "add to dList (state change!)"
					|	T  --> apply[car[exp],  evlis[cdr[exp],aList,dList],
																			aList, dList]  ]
	|	T		-->  "error!"  ]

 */
SExpression * Evaluator::eval(SExpression * exp, SExpression * Alist, SExpression ** Dlist){
    if(exp->getType() != NONATOM){
        if(isInt(exp) == CTRUE) return exp;
        else if(exp == CTRUE) return SExpression::symbolicAtom("T");
        else if (null(exp) == CTRUE) return SExpression::symbolicAtom("NIL");
        else if(isInAlist(exp,Alist)) return getValFromAlist(exp,Alist);
        else{
            throw std::runtime_error(">Error:: unbound variable");
            return NULL;
        }
    }
    else if (car(exp)->getType() != NONATOM){
        if(eq(car(exp),SExpression::symbolicAtom("QUOTE")) == CTRUE){
            return car(cdr(exp));
        }
        else if(eq(car(exp),SExpression::symbolicAtom("COND")) == CTRUE){
            return evCon(cdr(exp),Alist,*Dlist);
        }
        else if(eq(car(exp),SExpression::symbolicAtom("DEFUN")) == CTRUE){
            SExpression * newDlist = addFunctionToDlist(cdr(exp),*Dlist);
            *Dlist = newDlist;
            return SExpression::symbolicAtom(car(cdr(exp))->getName());
            //"add to dList
        }
        else{
            return apply(car(exp),evLis(cdr(exp),Alist,*Dlist),Alist,*Dlist);
        }
    }
    else{
        throw std::runtime_error(">Error:: nnfdsfa variable");
        return NULL;
    }
    throw std::runtime_error(">Error:: WTFs happening");
    return NULL;
}
SExpression * Evaluator::car(SExpression * expression){
    if(expression->getType()== NONATOM)
        return expression->getLeft();
    else
        throw std::runtime_error(">Error:: primitive CAR function called on atomic s-expression");
    return NULL;
}
SExpression * Evaluator::cdr(SExpression * expression){
    if(expression->getType()== NONATOM)
        return expression->getRight();
    else
        throw std::runtime_error(">Error:: primitive CDR function called on atomic s-expression");
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
        returnExp = (expression1->getVal() == expression2->getVal())?  SExpression::symbolicAtom("T") :  SExpression::symbolicAtom("NIL");
    }
    else if(expression1->getType() == SYMBOLICATOM && expression2->getType() == SYMBOLICATOM){
        bool a = expression1->getName() == expression2->getName();
        SExpression * b = SExpression::symbolicAtom("T");
        SExpression * c = SExpression::symbolicAtom("NIL");
        returnExp = a?  b :c;
        string ee = returnExp->getName();
    }
    else
        throw std::runtime_error(">Error:: primitive EQ function called on non-atomic s-expressions / invalid s-expressions");
    return returnExp;
}
SExpression * Evaluator::null(SExpression * expression){
    return (expression == SExpression::symbolicAtom("NIL"))? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
}
SExpression * Evaluator::isInt(SExpression * expression){
    return expression->getType() == INTEGERATOM? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
}
SExpression * Evaluator::plus(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal()+expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function PLUS. Called on non-atomic s-expressions / invalid s-expressions");

}
SExpression * Evaluator::minus(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal()-expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function PLUS. Called on non-atomic s-expressions / invalid s-expressions");

}
SExpression * Evaluator::times(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal() * expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function TIMES. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::quotient(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        //divide by zero
        newExp->setVal(expression1->getVal()/expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function QUOTIENT. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::reminder(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal() % expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function REMAINDER. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::less(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()<expression2->getVal()? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function LESS. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::greater(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()>expression2->getVal()? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function GREATER. Called on non-atomic s-expressions / invalid s-expressions");
}
SExpression * Evaluator::atom(SExpression * expression){
    return expression->getType()!=NONATOM? CTRUE: CFALSE;
}
bool Evaluator::isTrue(SExpression * exp){
    return exp==SExpression::symbolicAtom("T");
}
bool Evaluator::isInAlist(SExpression * symbolicAtomExp,SExpression * aList){
     if(symbolicAtomExp->getType() != SYMBOLICATOM) return false;
    if(symbolicAtomExp == car(car(aList))) return true;
    else return isInAlist(symbolicAtomExp,cdr(aList));
}
SExpression*  Evaluator::getValFromAlist(SExpression * symbolicAtomExp,SExpression * aList){
    //if(symbolicAtomExp->getType() != SYMBOLICATOM) return false;
    if(symbolicAtomExp == car(car(aList))) return cdr(car(aList));
    else return getValFromAlist(symbolicAtomExp,cdr(aList));
}
SExpression* Evaluator::addPairsToAList(SExpression * parameters, SExpression * arguments, SExpression * initialAList){
    if(null(parameters) == CTRUE && null(arguments) == CTRUE) return initialAList;
    else if(null(parameters) != CTRUE && null(arguments) != CTRUE) {
        SExpression * newpair = cons(car(parameters),car(arguments));
        return cons(newpair,addPairsToAList(cdr(parameters),cdr(arguments),initialAList));
    }
    else{
        throw std::runtime_error(">Error:: Mismatch in the expected number of argments and parameters");
    }

}
SExpression * Evaluator::addFunctionToDlist(SExpression * function, SExpression * initialDlist){
    SExpression * paramsAndBody = cons(car(cdr(function)), car(cdr(cdr(function))));
    SExpression * functionExp =  cons(car(function),paramsAndBody);
    SExpression * newDlist = cons(functionExp,initialDlist);
    return newDlist;
}
SExpression * Evaluator::getValFromDlist(SExpression* functionName, SExpression * dlist){
    if(isTrue(null(dlist)))
        throw std::runtime_error(">Error:: undeclared function:"+ functionName->getName());
    if(car(car(dlist)) == functionName){
        return cdr(car(dlist));
    } else{
        return getValFromDlist(functionName,cdr(dlist));
    }
}