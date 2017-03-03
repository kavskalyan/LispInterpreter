//
// Created by Kalyan Khandrika on 3/2/17.
//

#include "SExpression.h"

SExpression* SExpression::symbolicAtom(string str){
    SExpression * ne = new SExpression(SYMBOLICATOM);
    ne->setName(str);
    return ne;

}
SExpression::SExpression(SExpType aType):type(aType){

}
SExpType SExpression::getType() const {
    return type;
}

void SExpression::setType(SExpType type) {
    SExpression::type = type;
}

int SExpression::getVal() const {
    return val;
}

void SExpression::setVal(int val) {
    SExpression::val = val;
}

const string &SExpression::getName() const {
    return name;
}

void SExpression::setName(const string &name) {
    SExpression::name = name;
}

SExpression *SExpression::getLeft() const {
    return left;
}

void SExpression::setLeft(SExpression *left) {
    SExpression::left = left;
}

SExpression *SExpression::getRight() const {
    return right;
}

void SExpression::setRight(SExpression *right) {
    SExpression::right = right;
}
