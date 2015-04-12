#ifndef SNF_PARSER_H
#define SNF_PARSER_H

#include "string"
#include "vector"
#include <iostream>

enum FunctionType {
    SDNF, SKNF
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
public:

    int parse (std::string input, Expression &output);

    SNF_Parser();
};

#endif // SNF_PARSER_H
