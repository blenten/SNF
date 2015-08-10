#ifndef SNF_PARSER_H
#define SNF_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <sstream>
#include "../lvar.h"
#include "../Exceptions/invalidfunctionexception.h"
#include "classes/snf_parser/shortformconverter.h"
#include "../Types/types.h"

//Parser of string with SNF function
//NOTE: variables may delim by:
//operations: x1+x2, y1*y2
//brackets: (x1)(x2), (x1+x2)(x1+!x2), this will interpret as conjunction
//inverse: x1!x2!x3 as conjunction
//all spaces and unused symbols will be removed
//double inversions will be removed and replaced by conjunction symbol

enum OperationState
{
    UndefinedToDisjunction=-5,
    UndefinedToConjunction=-4,
    ConjunctionToDinsjunction=-3,
    DisjunctionToConjunction=-2,
    Undefined=-1,
    Conjunction=0,
    Disjunction=1
};

///PARSER
class SNF_Parser
{
private:

    std::string _input;

    void initialChecking();

    void removeUnused();
    void removeCommas();

    void checkBrackets();

    //inserts '&' instead of double invertion and after operand before left bracket or invertion and after right bracket before invertion
    void insertConjunctionSymbols();

    void checkInversions();

    bool isFunctionSeemsInShortForm();

    FunctionType parseShortForm(Expression &output);
    FunctionType parseExpandedForm(Expression &output);

    FunctionType getVariables (std::vector<std::string> & variables);

    //increases to invertion/operand/zero symbol
    size_t increaseIndexToVariable(size_t index);

    bool isVariablesRepeat(std::vector<std::string> &variables);

    //gets an operand and increase index to position after it
    std::string getOperand (size_t &index);

    OperationState getNextState(size_t &lena, OperationState prevState);

    OperationState getOperationStateAfterLBracket(size_t index, OperationState currState);

    void fillExpressionVector(Expression& expression, const FunctionType &ft,
                              const std::vector<string> &variables);

    void addOperandToVector (Expression & expression);

public:

    FunctionType parse (std::string input, Expression &output);
};

#endif // SNF_PARSER_H
