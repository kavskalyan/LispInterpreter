//
// Created by Kalyan Khandrika on 3/8/17.
//

#include "Parser.h"
#include "Token.h"
using namespace std;

#include <iostream>
Parser::Parser() {
    lexer.loadNextToken();
    while (lexer.checkNextToken().getType() != ENDOFINPUT){
        try{
            vector<SExpression *> outputExpVec;
            while(lexer.checkNextToken().getType() != ENDOFLINE ){
                if(lexer.checkNextToken().getType() == ENDOFINPUT) break;
                SExpression*  exp = inputRoutine1();
                outputExpVec.push_back(exp);
            }
            for( int i = 0; i < outputExpVec.size();i++){
                if(outputExpVec[i] != NULL) {
                    string out = stringifySExpression(outputExpVec[i]);
                    cout << "Output:" << out<<endl;
                }
                delete outputExpVec[i], outputExpVec[i] = NULL;
            }
            if(lexer.checkNextToken().getType() == ENDOFLINE)
                lexer.skipNextToken();


        }
        catch (const runtime_error&  error) {
            //cout<<"In catch, token:"<<checkNextToken().getToken()<<endl;
            std::cout << error.what() << endl;
            //skipNextToken();
            while(lexer.checkNextToken().getType() != ENDOFLINE){
                if(lexer.checkNextToken().getType() == ENDOFINPUT) break;
                lexer.skipNextToken();
            }
            if(lexer.checkNextToken().getType() == ENDOFLINE)
                lexer.skipNextToken();
            //cout<<"end of catch"<<endl;
        }
    }
}

SExpression* Parser::inputRoutine2() {
    Token token = lexer.checkNextToken();
    if(token.getType() == CLOSEBRACE){
        lexer.skipNextToken();
        return SExpression::symbolicAtom("NIL");
    }
    else if(token.getType() == SPACE){
        lexer.skipNextToken();
        SExpression * newExpression = new SExpression(NONATOM);
        newExpression->setLeft(inputRoutine1());
        newExpression->setRight(inputRoutine2());
        return newExpression;
    }
    else{
        throw std::runtime_error("**error: Invalid token in s-expression:"+token.getToken());
        return NULL;
    }
}


SExpression* Parser::inputRoutine1() {
    Token token = lexer.checkNextToken();

    if (token.getType() == OPENBRACE){
        Token token = lexer.checkNextToken();
        lexer.skipNextToken();
        if(lexer.checkNextToken().getType() == CLOSEBRACE) return inputRoutine2();
        SExpression * newExpression = new SExpression(NONATOM);
        SExpression * leftExpression = inputRoutine1();
        newExpression->setLeft(leftExpression);
        SExpression * rightExpression;
        Token nexttoken = lexer.checkNextToken();
        if(nexttoken.getType() == DOT){
            lexer.skipNextToken();
            rightExpression = inputRoutine1();
            nexttoken = lexer.checkNextToken();
            if(nexttoken.getType() != CLOSEBRACE){
                throw std::runtime_error("**error:Expected ')' ,found "+nexttoken.getToken() );
                return NULL;
            }
            else
            {
                lexer.skipNextToken();
            }

        }
        else {
            rightExpression = inputRoutine2();
        }
        newExpression->setRight(rightExpression);
        return  newExpression;
    }
    else if(token.getType() == IDENTIFIER){
        lexer.skipNextToken();
        return SExpression::symbolicAtom(token.getToken());
    }
    else if(token.getType() == INTEGER){
        //cout<<"INT"<<token.getToken()<<endl;
        SExpression * newIntegerExpression = new SExpression(INTEGERATOM);
        newIntegerExpression->setVal(stoi(token.getToken()));
        lexer.skipNextToken();
        return  newIntegerExpression;
    }
    else{
        throw std::runtime_error("**error: Invalid token in s-expression:"+token.getToken());
        //ERROR
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