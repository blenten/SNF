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
//all spaces and unused symbols will be removed

enum FunctionType {
    OTHER=-1, SDNF, SKNF
};

struct Element
{
  std::string variable;
  bool inverted;
};

typedef std::vector<Element> Operand;
typedef std::vector <Operand> Expression;

class SNF_Parser
{
private:
    enum SymbolTypes
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
     std::string _input;
    int getSymbolType(char symb);
    bool checkBrackets();
    void removeUnused();
    //gets an operand and increase index to position after delim
    std::string getOperand (int &index);
    void getVariables (std::vector<std::string> & variables);

public:

    FunctionType parse (std::string input, Expression &output);

};

#endif // SNF_PARSER_H
