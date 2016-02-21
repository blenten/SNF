#ifndef SNF_PARSERDECORATOR_H
#define SNF_PARSERDECORATOR_H
#include "shortformparser.h"
#include "expandedformparser.h"

class SNF_ParserFacade
{
private:

FunctionInputForm getFunctionInputForm (std::string input);
Parser* getParser(std::string input);

public:
    FunctionType parse(std::string input, Expression &output);
    FunctionType parse(std::string input, QMExp &output);
};

#endif // SNF_PARSERDECORATOR_H
