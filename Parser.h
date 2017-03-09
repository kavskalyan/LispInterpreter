//
// Created by Kalyan Khandrika on 3/8/17.
//

#ifndef LISPINTERPRETER_PARSER_H
#define LISPINTERPRETER_PARSER_H


#include "SExpression.h"
#include "Lexer.h"

class Parser {
public:
    Parser();
    Lexer lexer;
    SExpression * inputRoutine1();
    SExpression * inputRoutine2();
    string stringifySExpression(SExpression * exp);
};


#endif //LISPINTERPRETER_PARSER_H
