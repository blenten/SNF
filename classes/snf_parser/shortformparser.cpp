#include "shortformparser.h"

FunctionType ShortFormParser::parse(string input, Expression &output)
{
     expression = &output;
     _input = input;
     checkCorrectness();

    char operation = _input[0];

    _input.erase(0,2);
    _input.erase(_input.length()-1,1);

    parseNumbers();

    FunctionType ft = (getSymbolType(operation)==SYMBOL_CONJUNCTION) ? SNKF:SNDF;

    fillExpression();
    return ft;
}

void ShortFormParser::checkCorrectness()
{
    expression->clear();
    variables.clear();
    removeUseless();

    checkBrackets();
    checkDigitsAndCommas();
    removeDoubleCommas();
}

void ShortFormParser::removeUseless()
{
    size_t i = 0;
    while (getSymbolType(_input[i])!=SYMBOL_ZERO)
    {
        if (getSymbolType(_input[i])==SYMBOL_OTHER || getSymbolType(_input[i])==SYMBOL_SPACE)
            _input.erase(i,1);
        else i++;
    }
}

void ShortFormParser::checkBrackets()
{
    unsigned int lCount = 0, rCount = 0;
    size_t lIndex = 0, rIndex = 0;

    size_t len = _input.length();

    for (size_t i=0; i<len+1; i++)
    {
        if (getSymbolType(_input[i]) == SYMBOL_LBRACKET)
        {
            lCount++;
            lIndex = i;
        }
        else if (getSymbolType(_input[i]) ==SYMBOL_RBRACKET)
        {
            rCount++;
            rIndex = i;
        }
    }
    if (lCount!=1 || rCount!=1) throw InvalidFunctionException ("%TooManyBrackets");

    if (lIndex!=1 || rIndex!=len-1) throw InvalidFunctionException ("%IncorrectBracketPosition");
}

void ShortFormParser::checkDigitsAndCommas()
{
    size_t len = _input.length();

    if (getSymbolType(_input[firstDigitPos]) == SYMBOL_COMMA || getSymbolType(_input[len-2]) == SYMBOL_COMMA)
        throw InvalidFunctionException ("%ExcessiveComma");

    for (size_t i=firstDigitPos; i<len-1; i++)
        if (!isdigit(_input[i]) && getSymbolType(_input[i]) != SYMBOL_COMMA)
            throw InvalidFunctionException ("%IncorrectEnumeration@"+std::to_string(i));
}

void ShortFormParser::removeDoubleCommas()
{
     size_t len = _input.length();

    for (size_t i=firstDigitPos; i<len-1; i++)
    {
        if (getSymbolType(_input[i]) == SYMBOL_COMMA && getSymbolType(_input[i+1]) == SYMBOL_COMMA)
        {
            _input.erase(i,1);
            len--;
            i--;
        }
    }
}

void ShortFormParser::parseNumbers()
{
    std::stringstream stream (_input);
    std::string curr;

    while (std::getline(stream, curr, ','))
    {
        numbers.push_back(atoi(curr.c_str()));
    }
}

unsigned int ShortFormParser::calculateVariablesCount()
{
    int max=0;
    size_t len = numbers.size();
    for (size_t i=0; i<len; i++)
        if (numbers[i] > max) max = numbers[i];
    if (max==0) return 1;

    return floor(log2(max)) + 1;
}

void ShortFormParser::fillExpression()
{
    unsigned int varCount = calculateVariablesCount();
    unsigned int operandCount = numbers.size();

    for (unsigned int i=0; i<operandCount; i++)
    {
        Operand op;

        std::string str = numberToBinary(numbers[i], varCount);

        for (unsigned int j=0; j<varCount; j++)
        {
            Variable var;
            std::string currVar = 'x' + std::to_string(j+1);
            var.name = currVar;

            if (str[j]=='0') var.invertion = true;
            else var.invertion = false;

            op.push_back(var);
        }
       expression->push_back(op);
    }
}

std::string ShortFormParser::numberToBinary(int number, int size)
{
    std::string str;
    for (int j = 0; j < size; j++)
            str = ((number & (1 << j))? "1" : "0") + str;
    return str;
}
