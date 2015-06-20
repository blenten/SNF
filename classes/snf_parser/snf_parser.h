#ifndef SNF_PARSER_H
#define SNF_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <sstream>
#include "../lvar.h"
#include "../Exceptions/invalidfunctionexception.h"

//Parser of string with SNF function
//NOTE: variables may delim by:
//operations: x1+x2, y1*y2
//brackets: (x1)(x2), (x1+x2)(x1+!x2), this will interpret as conjunction
//inverse: x1!x2!x3 as conjunction
//all spaces and unused symbols will be removed
//double inversions will be removed

enum FunctionType {
    OTHER=-1, SNDF, SNKF
};

enum OperationState {
    UndefinedToDisjunction=-5,
    UndefinedToConjunction=-4,
    ConjunctionToDinsjunction=-3,
    DisjunctionToConjunction=-2,
    Undefined=-1,
    Conjunction=0,
    Disjunction=1
};

enum SymbolType
{
    SYMBOL_CONJUNCTION,
    SYMBOL_DISJUNCTION,
    SYMBOL_LBRACKET,
    SYMBOL_RBRACKET,
    SYMBOL_INVERSE,
    SYMBOL_OPERAND,
    SYMBOL_ZERO,
    SYMBOL_SPACE,
    SYMBOL_OTHER
};

///PARSER
class SNF_Parser
{
private:

    std::string _input;

    SymbolType getSymbolType(char symb);
    void checkBrackets();
    void removeUnused();

    //gets an operand and increase index to position after delim
    std::string getOperand (int &index);

   FunctionType getVariables (std::vector<std::string> & variables);

    void checkInversions();
    //inserts '&' instead of double inversion and after operand before left bracket
    void insertConjunctionSymbols();
    OperationState getOperationStateAfterLBracket(int index, OperationState currState);
    bool isVariablesRepeat(std::vector<std::string> &variables);

    void fillExpressionVector(Expression& expression, const FunctionType &ft,
                              std::vector<std::string> & variables);
    void addOperandToVector (Expression & expression);

    OperationState getNextState(int & lena, OperationState prevState);

public:

    FunctionType parse (std::string input, Expression &output);

};

#endif // SNF_PARSER_H
