//
// Created by Kalyan Khandrika on 3/2/17.
//

#include "FrontEnd.h"
#include <iostream>

FrontEnd::FrontEnd(){
    initializeInputStream();
    SExpression*  exp = inputRoutine1();
    if(exp!=NULL) {
        string out = stringifySExpression(exp);
        cout << "Output:" << out;
    }
}

SExpression* FrontEnd::inputRoutine2() {
    Token token = checkNextToken();
    if(token.getType() == CLOSEBRACE){
        cout<<"CBRACE END"<<endl;
        return SExpression::symbolicAtom("Nil");
    }
    else{
        cout<<"NON ATOM2"<<endl;
        SExpression * newExpression = new SExpression(NONATOM);
        newExpression->setLeft(inputRoutine1());
        //skipNextToken();
        newExpression->setRight(inputRoutine2());
        return newExpression;
    }
}

SExpression* FrontEnd::inputRoutine1() {
    Token token = checkNextToken();

    if (token.getType() == OPENBRACE){
        SExpression * newExpression = new SExpression(NONATOM);
        cout<<"OBARCE"<<endl;
        skipNextToken();
        SExpression * leftExpression = inputRoutine1();
        newExpression->setLeft(leftExpression);
        SExpression * rightExpression;
        Token nexttoken = checkNextToken();
        if(nexttoken.getType() == DOT){
            cout<<"DOT"<<endl;
            skipNextToken();
            rightExpression = inputRoutine1();
        }
        else if(nexttoken.getType() == SPACE){
            cout<<"SPACE"<<endl;
            skipNextToken();
            rightExpression = inputRoutine2();
        }
        else if(nexttoken.getType() == CLOSEBRACE){
            cout<<"CBARCE"<<endl;
            rightExpression = inputRoutine2();
            return newExpression;
        }
        else{
            return NULL;
            //ERROR
        }
        nexttoken = checkNextToken();
        if(nexttoken.getType() != CLOSEBRACE){
            return NULL;
            //ERROR
        }
        else
        {
            cout<<"CBARCE"<<endl;
        }
        skipNextToken();
        newExpression->setRight(rightExpression);
        return  newExpression;
    }
    else if(token.getType() == IDENTIFIER){
        skipNextToken();
        return SExpression::symbolicAtom(token.getToken());
    }
    else if(token.getType() == INTEGER){
        cout<<"INT"<<token.getToken()<<endl;
        SExpression * newIntegerExpression = new SExpression(INTEGERATOM);
        newIntegerExpression->setVal(stoi(token.getToken()));
        skipNextToken();
        return  newIntegerExpression;
    }
    else{
        return NULL;
        //ERROR
    }
}
void FrontEnd::initializeInputStream(){
    inputFileStream.open("../input.txt");
    //inputRoutine1();
}
Token FrontEnd::checkNextToken(){
    char c = inputFileStream.get();
    cout<<c<<endl;
    if ( c == '\t' || c == '\n')
        c = inputFileStream.get();
    Token newToken;
    if ( (c >= '0') && (c <= '9') )
    {
        int n;
        inputFileStream.putback (c);
        inputFileStream >> n;
        inputFileStream.unget();
        newToken.setType(INTEGER);
        newToken.setToken(to_string(n));

    }
    else if( (c >= 'A') && (c <= 'Z'))
    {
        std::string str;
        inputFileStream.putback (c);
        inputFileStream >> str;
        inputFileStream.unget();
        std::cout << "You entered a word: " << str << '\n';
        newToken.setType(IDENTIFIER);
        newToken.setToken(str);
    }
    else if( c == '(')
    {
        inputFileStream.putback (c);
        newToken.setType(OPENBRACE);
    }
    else if( c == ')')
    {
        inputFileStream.putback (c);
        newToken.setType(CLOSEBRACE);
    }
    else if( c == ' ')
    {
        inputFileStream.putback (c);
        newToken.setType(SPACE);
    }
    else if( c == '$')
    {
        inputFileStream.putback (c);
        newToken.setType(ENDOFLINE);
    }
    else if( c == '.')
    {
        inputFileStream.putback (c);
        newToken.setType(DOT);
    }
    else{
        cout<<"Safsa:"<<c<<endl;
    }
    return newToken;
}
void FrontEnd::skipNextToken(){
    char c = inputFileStream.get();
    if ( (c >= '0') && (c <= '9') )
    {
        int n;
        inputFileStream.putback (c);
        inputFileStream >> n;
    }
    else if( (c >= 'A') && (c <= 'Z'))
    {
        std::string str;
        inputFileStream.putback (c);
        inputFileStream >> str;
    }
    else if( c == '(' ||  c == ')' || c == ' ' || c == '$'  || c == '.')
    {

    }
    else{
        cout<<"Safsa:"<<c<<endl;
    }
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
