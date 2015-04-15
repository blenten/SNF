#ifndef SNF_PARSER_H
#define SNF_PARSER_H

#include "string"
#include "vector"
#include <iostream>
#include <ctype.h>

//Parser of string with SNF function
//NOTE: variables may delim by:
//operations: x1+x2, y1*y2
//brackets: (x1)(x2), (x1+x2)(x1+!x2), this will interpret as conjunction
//inverse: x1!x2!x3 as conjunction
//all spaces and unused symbols will be removed
//double inversions will be removed

enum FunctionType {
    OTHER=-1, SDNF, SKNF
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

struct Variable
{
  std::string variable;
  bool inverted;
};

typedef std::vector<Variable> Operand;
typedef std::vector <Operand> Expression;

class SNF_Parser
{
private:

    std::string _input;
    SymbolType getSymbolType(char symb);
    bool checkBrackets();
    void removeUnused();
    //gets an operand and increase index to position after delim
    std::string getOperand (int &index);
    std::string getOperandToFill (int &index);
   FunctionType getVariables (std::vector<std::string> & variables);

    bool checkInversions();
    OperationState getOperationStateAfterLBracket(int index, OperationState currState);
    bool isVariablesRepeat(std::vector<std::string> &variables);

    void fillExpressionVector(Expression& expression, FunctionType& ft,
                              std::vector<std::string> & variables);
    void addOperandToVector (Expression & expression);

    OperationState getNextState(int & lena, OperationState prevState);

public:

    FunctionType parse (std::string input, Expression &output);

};

#endif // SNF_PARSER_H
