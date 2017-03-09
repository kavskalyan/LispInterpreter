//
// Created by Kalyan Khandrika on 3/8/17.
//

#ifndef LISPINTERPRETER_LEXER_H
#define LISPINTERPRETER_LEXER_H

#include "Token.h"

class Lexer {
public:
    Token checkNextToken();
    void skipNextToken(bool isInCatchMode = false);
    void loadNextToken(bool isInCatchMode = false);
private:
    bool isIntegerTokenValid(string str);
    Token currentToken;
};


#endif //LISPINTERPRETER_LEXER_H
