//
// Created by Kalyan Khandrika on 3/21/17.
//

#include <iostream>
#include "Evaluator.h"
#define CTRUE SExpression::symbolicAtom("T")
#define  CFALSE SExpression::symbolicAtom("NIL")
/**
 * Evaluates the condition SExpression and returns the evaluated SExp
 * @param be
 * @param Alist
 * @param Dlist
 * @return
 */
SExpression * Evaluator::evCon(SExpression * be, SExpression * Alist, SExpression * Dlist){
    if(null(be) == CTRUE){
        throw std::runtime_error(">Error in evcon:: Condition cannot be nil");
        return NULL;//error
    }
    else if(eval(car(car(be)),Alist,&Dlist) != SExpression::symbolicAtom("NIL")){
            int conditionLength = lengthOfList(car(be));
            if(conditionLength != 2)
                throw std::runtime_error(">Error in evcon::Invalid number of arguments in Evcon");
            SExpression * cadarBE = car(cdr(car(be)));
            return eval(cadarBE,Alist,&Dlist);
    } else{
        return evCon(cdr(be),Alist,Dlist);
    }
}
/**
 * Evaluates the arguments in a list
 * @param list
 * @param Alist
 * @param Dlist
 * @return
 */
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
										|	eq[f, GREATER]		-->	greater[car[x], cadr[x]];
										|	eq[f, LESS]			-->	less[car[x], cadr[x]];
										|	eq[f, PLUS]			-->	plus[car[x], cadr[x]];
										|	eq[f, MINUS]		-->	minus[car[x], cadr[x]];
										|	eq[f, TIMES]		-->	times[car[x], cadr[x]];
										|	eq[f, QUOTIENT]		-->	quotient[car[x], cadr[x]];
										|	eq[f, REMINDER]		-->	reminder[car[x], cadr[x]];

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
            assertNumberOfArguments(function,arguments,1);
            returnVal = car(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("CDR")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = cdr(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("CONS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal =  cons(car(arguments),car(cdr(arguments))); //???
        } else if (eq(function, SExpression::symbolicAtom("NULL")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = null(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("EQ")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = eq(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("ATOM")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = atom(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("INT")) == CTRUE) {
            assertNumberOfArguments(function,arguments,1);
            returnVal = isInt(car(arguments));
        } else if (eq(function, SExpression::symbolicAtom("GREATER")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = greater(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("LESS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = less(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("PLUS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = plus(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("MINUS")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = minus(car(arguments),car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("TIMES")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = times(car(arguments), car(cdr(arguments)));
        } else if (eq(function, SExpression::symbolicAtom("QUOTIENT")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
            returnVal = quotient(car(arguments), car(cdr(arguments)));
        }else if (eq(function, SExpression::symbolicAtom("REMINDER")) == CTRUE) {
            assertNumberOfArguments(function,arguments,2);
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
        throw std::runtime_error(">Error:: Enexpected error");
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
            throw std::runtime_error(">Error:: Unbound variable:"+exp->getName());
            return NULL;
        }
    }
    else if (car(exp)->getType() != NONATOM){
        if(eq(car(exp),SExpression::symbolicAtom("QUOTE")) == CTRUE){
            assertNumberOfArguments(car(exp),cdr(exp),1);
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
        throw std::runtime_error(">Error:: Unexpected expression in eval");
        return NULL;
    }
    throw std::runtime_error(">Error:: Unexpected expression in eval");
    return NULL;
}
/**
 * CAR
 * @param SExpression
 * @return SExpression
 */
SExpression * Evaluator::car(SExpression * expression){
    if(expression->getType()== NONATOM)
        return expression->getLeft();
    else
        throw std::runtime_error(">Error:: primitive CAR function called on atomic s-expression");
    return NULL;
}
/**
 * CDR
 * @param SExpression
 * @return SExpression
 */
SExpression * Evaluator::cdr(SExpression * expression){
    if(expression->getType()== NONATOM)
        return expression->getRight();
    else
        throw std::runtime_error(">Error:: primitive CDR function called on atomic s-expression");
    return NULL;
}
/**
 * CONS constructs a non atomic Sexp with the two arguments
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::cons(SExpression * expression1,SExpression * expression2 ){
    SExpression * newExpression = new SExpression(NONATOM);
    newExpression->setLeft(expression1);
    newExpression->setRight(expression2);
    return newExpression;
}
/**
 * checks if both the sexpressions are equal if they are symbolic
 * If int, it checks for equal value
 * @param SExpression, SExpession
 * @return SExpression
 */
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
/**
 * checks if the sExp is null
 * @param SExpression
 * @return SExpression
 */
SExpression * Evaluator::null(SExpression * expression){
    return (expression == SExpression::symbolicAtom("NIL"))? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
}
/**
 * checks if the Sexp is int
 * @param SExpression
 * @return SExpression
 */
SExpression * Evaluator::isInt(SExpression * expression){
    return expression->getType() == INTEGERATOM? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
}
/**
 * returns the sum of the values in the two sexpressions
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::plus(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal()+expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function PLUS. Called on non-atomic s-expressions / invalid s-expressions");

}
/**
 * returns the difference of the values in the two sexpressions as another int SExpression
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::minus(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal()-expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function PLUS. Called on non-atomic s-expressions / invalid s-expressions");

}
/**
 * returns the product of the values in the two sexpressions as another int SExpression
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::times(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        newExp->setVal(expression1->getVal() * expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function TIMES. Called on non-atomic s-expressions / invalid s-expressions");
}
/**
 * returns the quotient when one expression is divided by the second and returns as another int SExpression
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::quotient(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        if(expression2->getVal()==0)
            std::runtime_error(">Error:: Division by 0 is not defined");
        newExp->setVal(expression1->getVal()/expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function QUOTIENT. Called on non-atomic s-expressions / invalid s-expressions");
}
/**
 * returns the reminder when one expression is divided by the second and returns as another int SExpression
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::reminder(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        SExpression * newExp = new SExpression(INTEGERATOM);
        if(expression2->getVal()==0)
            std::runtime_error(">Error:: Division by 0 is not defined");
        newExp->setVal(expression1->getVal() % expression2->getVal());
        //delete expression1, expression2;
        return  newExp;
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function REMAINDER. Called on non-atomic s-expressions / invalid s-expressions");
}
/**
 * returns the T symbolic atom is the first SEXP is less than the second
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::less(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()<expression2->getVal()? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function LESS. Called on non-atomic s-expressions / invalid s-expressions");
}
/**
 * returns the T symbolic atom is the first SExp is greater than the second
 * @param SExpression, SExpession
 * @return SExpression
 */
SExpression * Evaluator::greater(SExpression * expression1,SExpression * expression2 ){
    if(expression1->getType() == INTEGERATOM && expression2->getType() == INTEGERATOM){
        return expression1->getVal()>expression2->getVal()? SExpression::symbolicAtom("T"):SExpression::symbolicAtom("NIL");
    }
    throw std::runtime_error(">Error:: Types mismatch in primitive function GREATER. Called on non-atomic s-expressions / invalid s-expressions");
}
/**
 * returns the T symbolic atom is the the expression is atom
 * @param SExpression
 * @return SExpression
 */
SExpression * Evaluator::atom(SExpression * expression){
    return expression->getType()!=NONATOM? CTRUE: CFALSE;
}
/**
 * returns boolean true is the the expression is symbolic atom T
 * @param SExpression
 * @return bool
 */
bool Evaluator::isTrue(SExpression * exp){
    return exp==SExpression::symbolicAtom("T");
}
/**
 * returns true if the symbolic atom is in the Alist
 * @param symbolicAtomExp
 * @param aList
 * @return bool
 */
bool Evaluator::isInAlist(SExpression * symbolicAtomExp,SExpression * aList){
     if(symbolicAtomExp->getType() != SYMBOLICATOM) return false;
    if(aList == CFALSE) return false;
    if(symbolicAtomExp == car(car(aList))) return true;
    else return isInAlist(symbolicAtomExp,cdr(aList));
}
/**
 * returns the value of the symbolic atom is in the Alist
 * @param symbolicAtomExp
 * @param aList
 * @return SExpression
 */
SExpression*  Evaluator::getValFromAlist(SExpression * symbolicAtomExp,SExpression * aList){
    //if(symbolicAtomExp->getType() != SYMBOLICATOM) return false;
    if(symbolicAtomExp == car(car(aList))) return cdr(car(aList));
    else return getValFromAlist(symbolicAtomExp,cdr(aList));
}
/**
 * Associates the current arguments with the parameters and returns the pointer to the updated Alist
 * @param parameters
 * @param arguments
 * @param initialAList
 * @return
 */
SExpression* Evaluator::addPairsToAList(SExpression * parameters, SExpression * arguments, SExpression * initialAList){
    if(null(parameters) == CTRUE && null(arguments) == CTRUE) return initialAList;
    else if(null(parameters) != CTRUE && null(arguments) != CTRUE) {
        SExpression * newpair = cons(car(parameters),car(arguments));
        return cons(newpair,addPairsToAList(cdr(parameters),cdr(arguments),initialAList));
    }
    else{
        throw std::runtime_error(">Error:: Mismatch in the number of arguments and parameters");
    }

}
/**
 * Adds the function to the Dlist and returns the updated Dlist
 * @param function
 * @param initialDlist
 * @return
 */
SExpression * Evaluator::addFunctionToDlist(SExpression * function, SExpression * initialDlist){
    SExpression * paramsAndBody = cons(car(cdr(function)), car(cdr(cdr(function))));
    bool isParamsAList = isList(car(cdr(function)));
    if(isParamsAList == false)
        throw std::runtime_error(">Error:: Improper function definition:"+ car(function)->getName());
    if(cdr(cdr(cdr(function))) != CFALSE)
        throw std::runtime_error(">Error:: Improper function definition:"+ car(function)->getName());
    SExpression * functionExp =  cons(car(function),paramsAndBody);
    SExpression * newDlist = cons(functionExp,initialDlist);
    return newDlist;
}
/**
 * Returns the function node from the Dlist
 * @param functionName
 * @param dlist
 * @return
 */
SExpression * Evaluator::getValFromDlist(SExpression* functionName, SExpression * dlist){
    if(isTrue(null(dlist)))
        throw std::runtime_error(">Error:: undeclared function:"+ functionName->getName());
    if(car(car(dlist)) == functionName){
        return cdr(car(dlist));
    } else{
        return getValFromDlist(functionName,cdr(dlist));
    }
}
/**
 * Checks if the number of arguments passed are same as the expected number
 * @param funcName
 * @param arguments
 * @param numExpectedArguments
 */
void Evaluator::assertNumberOfArguments(SExpression* funcName,SExpression* arguments, int numExpectedArguments){
    int actualLengthOfArguments = lengthOfList(arguments);
    if( actualLengthOfArguments != numExpectedArguments)
        throw std::runtime_error(">Error:: Expected number of arguments:"+to_string(numExpectedArguments) + " and received:"+to_string(actualLengthOfArguments)+" for the primitive function:"+funcName->getName());
}
/**
 * Returns the length of a list given a SExpression to a list
 * @param list
 * @return
 */
int Evaluator::lengthOfList(SExpression * list){
    if(list == CFALSE)
        return 0;
    else return 1+lengthOfList(cdr(list));
}
bool Evaluator::isList(SExpression * exp){
    if(exp == CFALSE)
        return true;
    else if(exp->getType() == NONATOM)
        return  isList(exp->getRight());
    else
        return false;
}
