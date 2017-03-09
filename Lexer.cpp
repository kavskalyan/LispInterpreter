//
// Created by Kalyan Khandrika on 3/8/17.
//

#include "Lexer.h"
#include <iostream>

Token Lexer::checkNextToken(){
    return currentToken;

}

bool Lexer::isIntegerTokenValid(string str){
    //int len = str.l
    if(str[0] == '+' || str[0] =='-'){
        if(str.length()== 1) return false;
        for(int i = 1; i < str.length(); i++){
            if(str[i] <'0' || str[i] > '9')
                return false;
        }
    }
    return true;
}

void Lexer::skipNextToken(){
    loadNextToken();
    if(currentToken.getType() == INTEGER){
        if(!isIntegerTokenValid(currentToken.getToken())){
            throw std::runtime_error("**error: Invalid integer token in input:"+currentToken.getToken());
        }
    }
}
void Lexer::loadNextToken() {
    //istream inputFileStream = cin;
    Token newToken;
    bool breakToken = false;
    while(char c = cin.get()){
        //cout<<":"<<c<<":"<<endl;
        if ( (((c >= '0') && (c <= '9')) || (c == '+') || (c == '-')) )
        {
            if((newToken.getToken() != "" && newToken.getType() == INTEGER )|| newToken.getToken() == "" ){
                newToken.setToken(newToken.getToken()+c);
                newToken.setType(INTEGER);
            }
            else if(newToken.getToken() != "" && newToken.getType() == IDENTIFIER){
                newToken.setToken(newToken.getToken()+c);
            }
            else {
                //if(newToken.getToken() != ""){
                breakToken = true;
            }
        }
        else if( (c >= 'A') && (c <= 'Z'))
        {
            if((newToken.getToken() != "" && newToken.getType() == IDENTIFIER )|| newToken.getToken() == "" ){
                // cout<<"char"<<c;
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
                // break;
            }
            else if(newToken.getType() == ENDOFLINE){
                newToken.setType(ENDOFINPUT);
                newToken.setToken("$$");
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
            if(newToken.getType()== ENDOFLINE)
                break;
            if(c != '\n' && c != '\t' && c != ' ' && c!= '$'){
                string a (1,c);
                throw runtime_error("**error: Invalid character in input:'"+a+"'");
            }
        }
        if(breakToken){
            cin.unget();
            break;
        }
    }
    currentToken = newToken;
    //cout<<"Token:"<<currentToken.getToken()<<endl;
}