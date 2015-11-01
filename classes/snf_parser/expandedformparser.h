#ifndef EXPANDEDFORMPARSER_H
#define EXPANDEDFORMPARSER_H

#include "parser.h"

enum OperationState
{
    UndefinedToDisjunction = -5,
    UndefinedToConjunction = -4,
    ConjunctionToDinsjunction = -3,
    DisjunctionToConjunction = -2,
    Undefined = -1,
    Conjunction = 0,
    Disjunction = 1
};

class ExpandedFormParser: public Parser
{
private:    
    void initialChecking();
    void removeUseless();
    void checkBrackets();
    //inserts '&' instead of double inversion and after operand before left bracket or inversion and after right bracket before inversion
    void insertConjunctionSymbols();
    void checkInversions();

    FunctionType parseExpandedForm();

    FunctionType getVariables();

    //increases to inversion/operand/zero symbol
    size_t increaseIndexToVariable(size_t index);

    bool isVariablesRepeat();

    //gets an operand and increase index to position after it
    std::string getVariable (size_t &index);

    OperationState getNextState(size_t &lena, OperationState prevState);

    OperationState getOperationStateAfterLBracket(size_t index, OperationState currState);

    void fillExpression(const FunctionType &ft);

    void addOperandToExpression();

    Variable parseVariable(std::string &currVar);

public:
    FunctionType parse (std::string input, Expression &output);
};

#endif // EXPANDEDFORMPARSER_H
