//
// Created by Kalyan Khandrika on 3/2/17.
//

#ifndef LISPINTERPRETER_SEXPRESSION_H
#define LISPINTERPRETER_SEXPRESSION_H


#include <string>
#include <vector>
using namespace std;

enum SExpType{
    INTEGERATOM = 0,
    SYMBOLICATOM,
    NONATOM
};

class SExpression {
public:
    static SExpression* symbolicAtom(string s);
    SExpression(SExpType);
private:
    //SExpression(int);
    //SExpression(string);
    static vector<SExpression*> identifiers;
    SExpType type; /* 1: integer atom; 2: symbolic atom; 3: non-atom */
    int val; /* if type is 1 */
    std::string name; /* if type is 2 */
    SExpression * left; /* if type is 2 */
    SExpression * right; /* if type is 3 */
public:
    SExpType getType() const;

    void setType(SExpType type);

    int getVal() const;

    void setVal(int val);

    const string &getName() const;

    void setName(const string &name);

    SExpression *getLeft() const;

    void setLeft(SExpression *left);

    SExpression *getRight() const;

    void setRight(SExpression *right);
};


#endif //LISPINTERPRETER_SEXPRESSION_H
