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
    Disjunction = 0,
    Conjunction = 1
};

class ExpandedFormParser: public Parser
{
private:        
    void initialChecking();

    void removeUseless();
    void checkBrackets();
    void insertConjunctionSymbols();
    void checkInversions();  

    void parseExpandedForm();

    FunctionType getVariables();

    size_t increaseIndexToVariable(size_t index);

    bool isVariablesRepeat();

    std::string getVariable (size_t index);

    size_t increaseIndexToSymbolAfterVariable(size_t index);

    OperationState getNextState(size_t lena, OperationState prevState);

    OperationState getOperationStateAfterLeftBracket(size_t index, OperationState currState);

    void fillExpression();

    void addOperandToExpression();

    Variable parseVariable(std::string &currVar);

public:
    std::pair<Expression, FunctionType> parse (std::string input);
};

#endif // EXPANDEDFORMPARSER_H
