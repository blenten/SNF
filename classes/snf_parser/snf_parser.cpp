#include "snf_parser.h"

void SNF_Parser::removeUnused()
{
    size_t i=0;
    while (getSymbolType(_input[i])!=SYMBOL_ZERO)
    {
        if (getSymbolType(_input[i])==SYMBOL_OTHER || getSymbolType(_input[i])==SYMBOL_SPACE)
            _input.erase(i,1);
        else i++;
    }
}

bool SNF_Parser::checkOperation(const std::string & input)
{
  if (getSymbolType(input[0])!=SYMBOL_CONJUNCTION && getSymbolType(input[0])!=SYMBOL_DISJUNCTION)
     return false;
  return true;
}
