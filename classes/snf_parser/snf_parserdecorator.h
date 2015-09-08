#ifndef SNF_PARSERDECORATOR_H
#define SNF_PARSERDECORATOR_H
#include "shortformparser.h"
#include "expandedformparser.h"

class SNF_ParserDecorator
{
private:

FunctionInputForm getFunctionInputForm (std::string input);

public:
    FunctionType parse  (std::string input, Expression &output);
};

#endif // SNF_PARSERDECORATOR_H
