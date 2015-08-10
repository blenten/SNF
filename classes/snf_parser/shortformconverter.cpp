#include "shortformconverter.h"

std::string ShortFormConverter::_input;

std::string ShortFormConverter::convertToExpandedForm(std::string input)
{
    _input=input;
     checkCorrectness();

    std::string output;
    char operation=_input[0];
    char inOperandOperation = (getSymbolType(operation)==SYMBOL_CONJUNCTION)? '+':'&';

    _input.erase(0,2);
    _input.erase(_input.length()-1,1);

    std::vector<int> numbers;
    parseNumbers(numbers);

    unsigned int varCount = calculateVariablesCount(numbers);
    unsigned int operandCount = numbers.size();

    for (unsigned int i=0;i<operandCount;i++)
    {
        std::string str=numberToBinary(numbers[i], varCount);
        if (getSymbolType(operation)==SYMBOL_CONJUNCTION) output+='(';

        for (unsigned int j=0;j<varCount;j++)
        {
            std::string currVar = 'x'+std::to_string(j+1);
            if (str[j]=='0') output+='!';
            output+=currVar;
            if (j<varCount-1) output+=inOperandOperation;
        }

        if (getSymbolType(operation)==SYMBOL_CONJUNCTION) output+=')';
        if (i<operandCount-1)
        {
            output+= ' ';
            output+= operation;
            output+= ' ';
        }
    }
    return output;
}

void ShortFormConverter::checkCorrectness()
{
    if (!checkOperation(_input)) throw InvalidFunctionException ("%IncorrectShortForm");
    checkBrackets();
    checkDigitsAndCommas();
    removeDoubleCommas();
}

bool ShortFormConverter::checkOperation(const std::string & input)
{
  if (getSymbolType(input[0])!=SYMBOL_CONJUNCTION && getSymbolType(input[0])!=SYMBOL_DISJUNCTION)
     return false;
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

    for (size_t i=firstDigitPos;i<len-1;i++)
    {
        if (getSymbolType(_input[i])==SYMBOL_COMMA && getSymbolType(_input[i+1])==SYMBOL_COMMA)
        {
            _input.erase(i,1);
            len--;
            i--;
        }
    }
}

void ShortFormConverter::parseNumbers(std::vector<int> &numbers)
{
    std::stringstream stream (_input);
    std::string curr;

    while (std::getline(stream, curr, ','))
    {
        numbers.push_back(atoi(curr.c_str()));
    }
}

unsigned int ShortFormConverter::calculateVariablesCount(const std::vector<int> &numbers)
{
    int max=0;
    size_t len = numbers.size();
    for (size_t i=0;i<len;i++)
        if (numbers[i]>max) max=numbers[i];
    if (max==0) return 1;

    double logmax = log2(max);

    return floor(logmax)+1;
}

std::string ShortFormConverter::numberToBinary(int number, int size)
{
    std::string str;
    for (int j = 0; j < size; j++)
            str = ((number & (1 << j))? "1" : "0") + str;
    return str;
}
