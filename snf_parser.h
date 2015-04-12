#ifndef SNF_PARSER_H
#define SNF_PARSER_H

#include "string"
#include "vector"
#include <iostream>
#include <ctype.h>

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
    int functionType;
     std::string _input;
    int getSymbolType(char symb);
    bool checkBrackets();
    int getVariables (std::vector<std::string> & variables);

public:

    FunctionType parse (std::string input, Expression &output);

    SNF_Parser();
};

#endif // SNF_PARSER_H
