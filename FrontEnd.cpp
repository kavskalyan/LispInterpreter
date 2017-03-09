//
// Created by Kalyan Khandrika on 3/2/17.
//

#include "FrontEnd.h"
#include <iostream>
namespace {

}
FrontEnd::FrontEnd(){
    //initializeInputStream();
    loadNextToken();
    while (checkNextToken().getType() != ENDOFINPUT){
        try{
            vector<SExpression *> outputExpVec;
            while(checkNextToken().getType() != ENDOFLINE ){
                if(checkNextToken().getType() == ENDOFINPUT) break;
                SExpression*  exp = inputRoutine1();
                outputExpVec.push_back(exp);
            }
            for( int i = 0; i < outputExpVec.size();i++){
                if(outputExpVec[i] != NULL) {
                    string out = stringifySExpression(outputExpVec[i]);
                    cout << "Output:" << out<<endl;
                }
                delete outputExpVec[i], outputExpVec[i] = NULL;
            }
            if(checkNextToken().getType() == ENDOFLINE)
                skipNextToken();


        }
        catch (const runtime_error&  error) {
            //cout<<"In catch, token:"<<checkNextToken().getToken()<<endl;
            std::cout << error.what() << endl;
            //skipNextToken();
            while(checkNextToken().getType() != ENDOFLINE){
                if(checkNextToken().getType() == ENDOFINPUT) break;
                skipNextToken();
            }
            if(checkNextToken().getType() == ENDOFLINE)
                skipNextToken();
            //cout<<"end of catch"<<endl;
        }
    }



}

//SExpression* FrontEnd:: inputRoutine1OpenBrace(){
//    Token token = checkNextToken();
//    skipNextToken();
//    if(checkNextToken().getType() == CLOSEBRACE) return inputRoutine2();
//    SExpression * newExpression = new SExpression(NONATOM);
//    SExpression * leftExpression = inputRoutine1();
//    newExpression->setLeft(leftExpression);
//    SExpression * rightExpression;
//    Token nexttoken = checkNextToken();
//    if(nexttoken.getType() == DOT){
//        skipNextToken();
//        rightExpression = inputRoutine1();
//        nexttoken = checkNextToken();
//        if(nexttoken.getType() != CLOSEBRACE){
//            throw std::runtime_error("**error:Expected ')' ,found "+nexttoken.getToken() );
//            return NULL;
//        }
//        else
//        {
//            skipNextToken();
//        }
//
//    }
//    else {
//        rightExpression = inputRoutine2();
//    }
//    newExpression->setRight(rightExpression);
//    return  newExpression;
//}

void FrontEnd::initializeInputStream(){
    //inputFileStream.open("../input.txt");
//    inputFileStream = cin;
}
string FrontEnd::stringifySExpression(SExpression * exp){
    string outString;
    switch(exp->getType()){
        case NONATOM:
            outString+= '(';
            outString += stringifySExpression(exp->getLeft());
            outString += '.';
            outString += stringifySExpression(exp->getRight());
            outString += ')';
            break;
        case INTEGERATOM:
            outString += to_string(exp->getVal());
            break;
        case SYMBOLICATOM:
            outString += exp->getName();
            break;
        default:
            break;

    }
    return outString;
}