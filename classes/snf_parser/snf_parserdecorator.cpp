#include "snf_parserdecorator.h"

FunctionType SNF_ParserDecorator::parse(string input, Expression &output)
{
    Parser* parser;
    if (isInShortForm(input))parser = new ShortFormParser;
    else parser = new ExpandedFormParser;

    FunctionType ft = parser->parse(input,output);
    delete parser;
    return ft;
}

bool SNF_ParserDecorator::isInShortForm(string input)
{
    size_t i=0;
    while (getSymbolType(input[i])==SYMBOL_OTHER || getSymbolType(input[i])==SYMBOL_SPACE) i++;

    if (getSymbolType(input[i]) == SYMBOL_CONJUNCTION || getSymbolType(input[i]) == SYMBOL_DISJUNCTION )
        return true;
    return false;
}