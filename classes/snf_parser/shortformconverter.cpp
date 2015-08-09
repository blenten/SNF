#include "shortformconverter.h"

std::string ShortFormConverter::_input;

std::string ShortFormConverter::tryConvertToExpandedForm(std::string input)
{
    _input=input;
    if (!isFunctionInCorrectShortForm()) return input;

    std::string output;
    char operation=_input[0];

    _input.erase(0,2);
    _input.erase(_input.length()-1,1);


}

bool ShortFormConverter::isFunctionInCorrectShortForm()
{
    if (getSymbolType(_input[0])!=SYMBOL_CONJUNCTION && getSymbolType(_input[0])!=SYMBOL_DISJUNCTION)
        return false;

    checkBrackets();
    checkDigitsAndCommas();
    removeDoubleCommas();

    return true;
}

void ShortFormConverter::checkBrackets()
{
    unsigned int lCount=0, rCount=0;
    size_t lIndex=0, rIndex=0;

    size_t len=_input.length();

    for (size_t i=0;i<len+1;i++)
    {
        if (getSymbolType(_input[i])== SYMBOL_LBRACKET)
        {
            lCount++;
            lIndex=i;
        }
        else if (getSymbolType(_input[i])==SYMBOL_RBRACKET)
        {
            rCount++;
            rIndex=i;
        }
    }
    if (lCount!=1 || rCount!=1) throw InvalidFunctionException ("%IncorrectShortForm");

    if (lIndex!=1 || rIndex!=len-1) throw InvalidFunctionException ("%IncorrectShortForm");
}

void ShortFormConverter::checkDigitsAndCommas()
{
    size_t len=_input.length();

    for (size_t i=firstDigitPos;i<len-1;i++)
        if (!isdigit(_input[i]) && getSymbolType(_input[i])!=SYMBOL_COMMA)
            throw InvalidFunctionException ("%IncorrectShortForm");

    if (getSymbolType(_input[firstDigitPos])==SYMBOL_COMMA || getSymbolType(_input[len-2])==SYMBOL_COMMA)
        throw InvalidFunctionException ("%IncorrectShortForm");
}

void ShortFormConverter::removeDoubleCommas()
{
     size_t len=_input.length();

    for (size_t i=2;i<len-1;i++)
    {
        if (getSymbolType(_input[i])==SYMBOL_COMMA && getSymbolType(_input[i+1])==SYMBOL_COMMA)
        {
            _input.erase(i,1);
            len--;
            i--;
        }
    }
}
