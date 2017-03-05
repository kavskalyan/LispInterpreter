//
// Created by Kalyan Khandrika on 3/2/17.
//

#ifndef LISPINTERPRETER_FRONTEND_H
#define LISPINTERPRETER_FRONTEND_H

#include "SExpression.h"
#include "Token.h"
#include <fstream>

class FrontEnd {
public:
    FrontEnd();
    string stringifySExpression(SExpression *);
private:
    SExpression * inputRoutine1();
    SExpression * inputRoutine1OpenBrace();
    SExpression * inputRoutine1OpenBraceIdentifier();
    SExpression * inputRoutine2();
    Token checkNextToken();
    void skipNextToken(Token tkn);
    void loadNextToken();

    Token currentToken;
    Token previousToken;
    void initializeInputStream();
    fstream inputFileStream;

};


#endif //LISPINTERPRETER_FRONTEND_H
