//
// Created by Kalyan Khandrika on 3/2/17.
//

#include "Token.h"

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
