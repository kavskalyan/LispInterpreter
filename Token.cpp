//
// Created by Kalyan Khandrika on 3/2/17.
//

#include "Token.h"

#include <regex>
#include <iostream>
namespace {

    string findIntegerMatch(string subject){
        std::string result;
        try {
            regex r("^(\\\\+|-)?[[:digit:]]+");
            std::smatch match;
            if (std::regex_search(subject, match, r) && match.size() > 1) {
                result = match.str(1);
            } else {
                result = std::string("dsd");
            }
        } catch (std::regex_error& e) {
            // Syntax error in the regular expression
        }
        cout<<"Finding intermatch in "<<subject<<",found:"<<result<<endl;
        return result;

    }

    string findIdentifierMatch(string subject) {
        std::string result;
        try {
            regex r("^(\\\\+|-)?[A-Z]+");
            std::smatch match;
            if (std::regex_search(subject, match, r) && match.size() > 1) {
                result = match.str(1);
            } else {
                result = std::string("");
            }
        } catch (std::regex_error& e) {
            // Syntax error in the regular expression
        }
        return result;
    }
}
/*
 static queue<Token> Token::Tokenize(istream inputFileStream) {
    queue<Token> result;
    while(char c = inputFileStream.get()){
        Token newToken;
        if ( ((c >= '0') && (c <= '9')) || (c == '+') || (c == '-') )
        {
            string str;
            regex r("(\\+|-)?[[:digit:]]+");
            inputFileStream.putback (c);
            inputFileStream >> str;
            string result = findIntegerMatch(str);
            inputFileStream.unget();
            newToken.setType(INTEGER);
            newToken.setToken(result);

        }
        else if( (c >= 'A') && (c <= 'Z'))
        {
            std::string str;
            str+=c;
            //inputFileStream.putback (c);
            inputFileStream >> str;
            string result = findIdentifierMatch(str);
            inputFileStream.unget();
            std::cout << "You entered a word: " << str << '\n';
            newToken.setType(IDENTIFIER);
            newToken.setToken(result);
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
        result.push(newToken);
    }

    //return newToken;
}
*/
TokenType Token::getType() const {
    return type;
}

void Token::setType(TokenType type) {
    Token::type = type;
}

const string &Token::getToken() const {
    return token;
}

void Token::setToken(const string &token) {
    Token::token = token;
}
