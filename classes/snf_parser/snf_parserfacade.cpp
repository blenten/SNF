#include "snf_parserfacade.h"

FunctionType SNF_ParserFacade::parse(string input, Expression &output)
{
    Parser* parser = getParser(input);

    FunctionType ft = parser->parse(input,output);
    delete parser;
    return ft;
}

FunctionInputForm SNF_ParserFacade::getFunctionInputForm(string input)
{
    size_t i=0;
    while (getSymbolType(input[i])==SYMBOL_OTHER || getSymbolType(input[i])==SYMBOL_SPACE) i++;

    if (getSymbolType(input[i]) == SYMBOL_CONJUNCTION || getSymbolType(input[i]) == SYMBOL_DISJUNCTION )
        return FORM_SHORT;
    return FORM_EXPANDED;
}

FunctionType SNF_ParserFacade::parse(string input, QMExp &output)
{
    Parser* parser = getParser(input);
    Expression ex;
    FunctionType ft = parser->parse(input, ex);
    output = parser->expressionToQMExp(ex);

    delete parser;

    return ft;
}

Parser* SNF_ParserFacade::getParser(std::string input)
{
    Parser* parser;
    if (getFunctionInputForm(input) == FORM_SHORT)
        parser = new ShortFormParser;
    else parser = new ExpandedFormParser;

    return parser;
}
