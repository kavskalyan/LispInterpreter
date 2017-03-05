//
// Created by Kalyan Khandrika on 3/2/17.
//

#include "FrontEnd.h"
#include <iostream>

FrontEnd::FrontEnd(){
    initializeInputStream();
    loadNextToken();
    try{
        SExpression*  exp = inputRoutine1();
        if(exp!=NULL) {
            string out = stringifySExpression(exp);
            cout << "Output:" << out;
        }
    }
    catch (int i) {
        std::cout << " the integer exception was caught, with value: " << i << '\n';
    }


}

SExpression* FrontEnd::inputRoutine2() {
    Token token = checkNextToken();
    if(token.getType() == CLOSEBRACE){
        //cout<<"CBRACE END"<<endl;
        return SExpression::symbolicAtom("Nil");
    }
    else if(token.getType() == SPACE){
        skipNextToken(token);
       // cout<<"NON ATOM2"<<endl;
        SExpression * newExpression = new SExpression(NONATOM);
        newExpression->setLeft(inputRoutine1());
        //skipNextToken();
        newExpression->setRight(inputRoutine2());
        return newExpression;
    }
    else{
        throw 3;
    }
}
SExpression* FrontEnd:: inputRoutine1OpenBrace(){
    Token token = checkNextToken();
    SExpression * newExpression = new SExpression(NONATOM);
    skipNextToken(token);
    SExpression * leftExpression = inputRoutine1();
    newExpression->setLeft(leftExpression);
    SExpression * rightExpression;
    Token nexttoken = checkNextToken();
    if(nexttoken.getType() == DOT){
        //   cout<<"DOT"<<endl;
        skipNextToken(nexttoken);
        rightExpression = inputRoutine1();
    }
    else if(nexttoken.getType() == SPACE){
        rightExpression = inputRoutine2();
    }
    else if(nexttoken.getType() == CLOSEBRACE){
       rightExpression = inputRoutine2();
        //return newExpression;
    }
    else{
        throw 2;
        return NULL;
        //ERROR
    }
    nexttoken = checkNextToken();
    if(nexttoken.getType() != CLOSEBRACE){
        throw 1;
        return NULL;
        //ERROR
    }
    else
    {
        skipNextToken(nexttoken);
        cout<<"CBARCE"<<endl;
    }
    newExpression->setRight(rightExpression);
    return  newExpression;
}

SExpression* FrontEnd::inputRoutine1() {
    Token token = checkNextToken();

    if (token.getType() == OPENBRACE){
        return inputRoutine1OpenBrace();
    }
    else if(token.getType() == IDENTIFIER){
        skipNextToken(token);
        return SExpression::symbolicAtom(token.getToken());
    }
    else if(token.getType() == INTEGER){
        cout<<"INT"<<token.getToken()<<endl;
        SExpression * newIntegerExpression = new SExpression(INTEGERATOM);
        newIntegerExpression->setVal(stoi(token.getToken()));
        skipNextToken(token);
        return  newIntegerExpression;
    }
    else{
        return NULL;
        //ERROR
    }
}
void FrontEnd::initializeInputStream(){
    inputFileStream.open("../input.txt");
}
Token FrontEnd::checkNextToken(){
    return currentToken;

}
void FrontEnd::skipNextToken(Token tkn){
    //previousToken = currentToken;
    loadNextToken();
}
void FrontEnd::loadNextToken() {
    Token newToken;
    bool breakToken = false;
    while(char c = inputFileStream.get()){
       //cout<<":"<<c<<":"<<endl;
        if ( (((c >= '0') && (c <= '9')) || (c == '+') || (c == '-')) )
        {
            if((newToken.getToken() != "" && newToken.getType() == INTEGER )|| newToken.getToken() == "" ){
                newToken.setToken(newToken.getToken()+c);
                newToken.setType(INTEGER);
            }
            else {
            //if(newToken.getToken() != ""){
                breakToken = true;
            }
        }
        else if( (c >= 'A') && (c <= 'Z'))
        {
            if((newToken.getToken() != "" && newToken.getType() == IDENTIFIER )|| newToken.getToken() == "" ){
                cout<<"char"<<c;
                newToken.setToken(newToken.getToken()+c);
                newToken.setType(IDENTIFIER);
            }
            else {
                //if(newToken.getToken() != ""){
                breakToken = true;
            }
        }
        else if( c == '(')
        {
            if(newToken.getToken() == "" || (newToken.getType() == SPACE && currentToken.getType()==DOT)){
                newToken.setType(OPENBRACE);
                newToken.setToken("(");
                break;
            }
            else if(newToken.getType() == INTEGER || newToken.getType() == IDENTIFIER || newToken.getType() == SPACE){
                breakToken = true;
            }

        }
        else if( c == ')')
        {
            if(newToken.getToken() == "" || newToken.getType() == SPACE){
                newToken.setType(CLOSEBRACE);
                newToken.setToken(")");
                break;
            }
            else if(newToken.getType() == INTEGER || newToken.getType() == IDENTIFIER){
                breakToken = true;
            }
        }
        else if( c == ' ')
        {
            if(newToken.getToken() == "" || newToken.getType() == SPACE){
                if(currentToken.getType() == INTEGER || currentToken.getType() == IDENTIFIER || currentToken.getType() == CLOSEBRACE){
                    newToken.setType(SPACE);
                    newToken.setToken(" ");
                }
            }
            else if (newToken.getType() == INTEGER || newToken.getType() == IDENTIFIER){
                breakToken = true;
            }

        }
        else if( c == '$')
        {
            if(newToken.getToken() == "" || newToken.getType() == SPACE){
                newToken.setType(ENDOFLINE);
                newToken.setToken("$");
                break;
            }
            else if(newToken.getType() == INTEGER || newToken.getType() == IDENTIFIER){
                breakToken = true;
            }
        }
        else if( c == '.')
        {
            if(newToken.getToken() == "" || newToken.getType() == SPACE){
                newToken.setType(DOT);
                newToken.setToken(".");
                break;
            }
            else if(newToken.getType() == INTEGER || newToken.getType() == IDENTIFIER){
                breakToken = true;
            }
        }
        else{
            cout<<"Safsa:"<<c<<endl;
        }
        if(breakToken){
            inputFileStream.unget();
            break;
        }
    }
    currentToken = newToken;
    cout<<"Token:"<<currentToken.getToken()<<endl;
}
string FrontEnd::stringifySExpression(SExpression * exp){
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