//
// Created by Kalyan Khandrika on 3/2/17.
//

#include "SExpression.h"
map<string,SExpression*> SExpression::identifiers;

void SExpression::InitializeDefaultSymbolizAtoms(){
    SExpression * nilExp = new SExpression(SYMBOLICATOM);
    nilExp->setName("NIL");
    identifiers["NIL"] = nilExp;
    SExpression * trueExp = new SExpression(SYMBOLICATOM);
    trueExp->setName("T");
    identifiers["T"] = trueExp;
}
void SExpression::DeleteSymbolicAtoms(){
    for(auto it = identifiers.begin();it != identifiers.end(); it++){
        SExpression * symAtom = it->second;
        it->second = NULL;
        delete(symAtom);

    }

}
SExpression* SExpression::symbolicAtom(string str){
    if(identifiers.find(str) == identifiers.end() || identifiers[str] == NULL){
        SExpression * ne = new SExpression(SYMBOLICATOM);
        ne->setName(str);
        identifiers[str] = ne;
        return ne;
    }
    else
        return identifiers[str];

}
SExpression::~SExpression(){
    if(getType() == NONATOM){
        delete getLeft();
        delete getRight();
    }

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
