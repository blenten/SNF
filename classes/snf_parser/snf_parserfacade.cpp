#include "snf_parserfacade.h"

std::pair<Expression, FunctionType> SNF_ParserFacade::parse(string input)
{
    Parser* parser = getParser(input);    
    Expression output;
    FunctionType ft;

    std::tie(output, ft) = parser->parse(input);

    delete parser;
    return std::make_pair(output, ft);
}

std::pair<QMExp, FunctionType> SNF_ParserFacade::parse(QString input)
{
    Parser* parser = getParser(input.toStdString());

    Expression output;
    FunctionType ft;
    std::tie (output, ft) = parser->parse(input.toStdString());

    delete parser;
    return std::make_pair(parser->expressionToQMExp(output), ft);
}

FunctionInputForm SNF_ParserFacade::getFunctionInputForm(string input)
{
    size_t i=0;
    while (getSymbolType(input[i])==SYMBOL_OTHER || getSymbolType(input[i])==SYMBOL_SPACE) i++;

    if (getSymbolType(input[i]) == SYMBOL_CONJUNCTION || getSymbolType(input[i]) == SYMBOL_DISJUNCTION )
        return FORM_SHORT;
    return FORM_EXPANDED;
}

Parser* SNF_ParserFacade::getParser(std::string input)
{
    Parser* parser;
    if (getFunctionInputForm(input) == FORM_SHORT)
        parser = new ShortFormParser;
    else parser = new ExpandedFormParser;

    return parser;
}

