//
// Created by Kalyan Khandrika on 3/2/17.
//

#ifndef LISPINTERPRETER_TOKEN_H
#define LISPINTERPRETER_TOKEN_H

#include <string>
#include <queue>
#include <istream>

using namespace std;

enum TokenType{
    OPENBRACE = 0,
    CLOSEBRACE,
    DOT,
    IDENTIFIER,
    INTEGER,
    SPACE,
    ENDOFLINE, //$
    ENDOFINPUT //$$
};

class Token {
public:
   // static queue<Token> Tokenize(istream sstream);
    TokenType getType() const;

    void setType(TokenType type);

    const string &getToken() const;

    void setToken(const string &token);

private:
    string token;
    TokenType type;
};


#endif //LISPINTERPRETER_TOKEN_H
