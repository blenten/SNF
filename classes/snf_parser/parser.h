#ifndef SNF_PARSER_H
#define SNF_PARSER_H

#include "../operand.h"
#include "../Exceptions/invalidfunctionexception.h"
#include "../Types/types.h"
#include <cstdint>
#include <cmath>

//Parser of string with SNF function
//NOTE: variables may delim by:
//operations: x1+x2, y1*y2
//brackets: (x1)(x2), (x1+x2)(x1+!x2), this will interpret as conjunction
//inverse: x1!x2!x3 as conjunction
//all spaces and unused symbols will be removed
//double inversions will be removed and replaced by conjunction symbol
//function can be inputted in short form (e.g. +(1,3,5) means !x1*!x2*x3 + !x1*x2*x3 + x1*!x2*x3)

class Parser
{
protected:
    std::string _input;

    Expression *expression;
    std::vector <std::string> variables;
public:
    virtual FunctionType parse (std::string input, Expression &output) = 0;
    virtual ~Parser();
};

#endif // SNF_PARSER_H
