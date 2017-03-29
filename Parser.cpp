//
// Created by Kalyan Khandrika on 3/8/17.
//

#include "Parser.h"
#include "Token.h"
#include "Evaluator.h"
using namespace std;

#include <iostream>
Parser::Parser() {
    cout<<"Started>>>>>>>>>"<<endl;
    lexer.loadNextToken();
    SExpression::InitializeDefaultSymbolizAtoms();
    Evaluator evaluator;
    SExpression * Alist = SExpression::symbolicAtom("NIL");
    SExpression * pDList = SExpression::symbolicAtom("NIL");
    SExpression ** Dlist = &pDList;
    while (lexer.checkNextToken().getType() != ENDOFINPUT){
        try{
           // cout<<"Here";
            SExpression *  outputExp = NULL;
            if(lexer.checkNextToken().getType() != ENDOFLINE ){
                if(lexer.checkNextToken().getType() == ENDOFINPUT) break;
                outputExp = inputRoutine1();
            }
            if(lexer.checkNextToken().getType() == ENDOFLINE|| lexer.checkNextToken().getType() == ENDOFINPUT) {
                string outString = stringifySExpression(outputExp);
                cout << "Output before eval>" << outString << endl;
                outputExp = evaluator.eval(outputExp,Alist,Dlist);
                outString = stringifySExpression(outputExp);
                cout << "Output after eval>" << outString << endl;
                if(lexer.checkNextToken().getType() == ENDOFINPUT)
                    break;
                //cout <<"Input:";
                lexer.skipNextToken();
            }
            else
                throw std::runtime_error(">Error:: Invalid token after valid s-expression:"+lexer.checkNextToken().getToken());


        }
        catch (const runtime_error&  error) {
            //cout<<"In catch, token:"<<checkNextToken().getToken()<<endl;
            std::cout << error.what() << endl;
            bool bIgnoredChars = false;
            if(lexer.checkNextToken().getType() != ENDOFLINE && lexer.checkNextToken().getType() != ENDOFINPUT){
                cout<<"Ignoring characters:";
                bIgnoredChars = true;
            }
            while(lexer.checkNextToken().getType() != ENDOFLINE){
                if(lexer.checkNextToken().getType() == ENDOFINPUT) break;
                cout<<lexer.checkNextToken().getToken()<<",";
                lexer.skipNextToken(true);
            }
            if(bIgnoredChars)
                cout<<endl;
            if(lexer.checkNextToken().getType() == ENDOFLINE)
                lexer.skipNextToken(true);
            //cout<<"end of catch"<<endl;
        }
    }
    cout<<"End of program"<<endl;
}
Parser::~Parser() {
    SExpression::DeleteSymbolicAtoms();
}
/***
 * Grammar:
 * <ls>  :== <IR1>
 * <IR1> :== INT | ID | ( <IR1> . <IR1> ) |  ( <IR1><IR2> | ()
 * <IR2> :== ) |  [SPACE]<IR1><IR2>
 * @return
 */

// Corresponding to grammar: <ls>  :== <IR1>
SExpression* Parser::inputRoutine1() {
    Token token = lexer.checkNextToken();
    //<IR1> :==  ( <IR1> . <IR1> ) |  ( <IR1><IR2> | ()
    if (token.getType() == OPENBRACE){
        Token token = lexer.checkNextToken();
        lexer.skipNextToken();
        ////<IR1> :==  ()
        if(lexer.checkNextToken().getType() == CLOSEBRACE)
            return inputRoutine2();
        SExpression * newExpression = new SExpression(NONATOM);
        SExpression * leftExpression = inputRoutine1();
        newExpression->setLeft(leftExpression);
        SExpression * rightExpression;
        Token nexttoken = lexer.checkNextToken();
        //<IR1> :==  ( <IR1> .
        if(nexttoken.getType() == DOT){
            lexer.skipNextToken();
            //<IR1> :==  ( <IR1> . <IR1>
            rightExpression = inputRoutine1();
            nexttoken = lexer.checkNextToken();
            //<IR1> :==  ( <IR1> . <IR1> )
            if(nexttoken.getType() != CLOSEBRACE){
                throw std::runtime_error(">Error::Expected ')' ,found "+nexttoken.getToken() );
                return NULL;
            }
            else
            {
                lexer.skipNextToken();
            }

        }
            //<IR1> :==  ( <IR1><IR2>
        else {
            rightExpression = inputRoutine2();
        }
        newExpression->setRight(rightExpression);
        return  newExpression;
    }
    // <IR1> :== ID
    else if(token.getType() == IDENTIFIER){
        lexer.skipNextToken();
        return SExpression::symbolicAtom(token.getToken());
    }
        // <IR1> :== INT
    else if(token.getType() == INTEGER){
        //cout<<"INT"<<token.getToken()<<endl;
        SExpression * newIntegerExpression = new SExpression(INTEGERATOM);
        newIntegerExpression->setVal(stoi(token.getToken()));
        lexer.skipNextToken();
        return  newIntegerExpression;
    }
    else{
        throw std::runtime_error(">Error:: Invalid token in s-expression:"+token.getToken());
        //ERROR
    }
}
//<IR2> :== ) |  [SPACE]<IR1><IR2>
SExpression* Parser::inputRoutine2() {
    Token token = lexer.checkNextToken();
    //<IR2> :== )
    if(token.getType() == CLOSEBRACE){
        lexer.skipNextToken();
        return SExpression::symbolicAtom("NIL");
    }
        //<IR2> :== [SPACE]<IR1><IR2>
    else if(token.getType() == SPACE){
        lexer.skipNextToken();
        SExpression * newExpression = new SExpression(NONATOM);
        newExpression->setLeft(inputRoutine1());
        newExpression->setRight(inputRoutine2());
        return newExpression;
    }
    else{
        throw std::runtime_error(">Error:: Invalid token in s-expression:"+token.getToken());
        return NULL;
    }
}


string Parser::stringifySExpression(SExpression * exp){
    string outString;
    switch(exp->getType()){
        case NONATOM:
            outString+= '(';
            outString += stringifySExpression(exp->getLeft());
            outString += '.';
            outString += stringifySExpression(exp->getRight());
            outString += ')';
            break;
        case INTEGERATOM:
            outString += to_string(exp->getVal());
            break;
        case SYMBOLICATOM:
            outString += exp->getName();
            break;
        default:
            break;

    }
    return outString;
}