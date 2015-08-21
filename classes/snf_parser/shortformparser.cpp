#include "shortformparser.h"

FunctionType ShortFormParser::parse(string input, Expression &output)
{
     expression=&output;
     _input=input;
     checkCorrectness();

    char operation=_input[0];

    _input.erase(0,2);
    _input.erase(_input.length()-1,1);

    std::vector<int> numbers;
    parseNumbers(numbers);

    unsigned int varCount = calculateVariablesCount(numbers);
    unsigned int operandCount = numbers.size();

    FunctionType ft = (getSymbolType(operation)==SYMBOL_CONJUNCTION)? SNKF:SNDF;

    for (unsigned int i=0;i<operandCount;i++)
    {
        Operand op;


        std::string str=numberToBinary(numbers[i], varCount);
        for (unsigned int j=0;j<varCount;j++)
        {
            Variable var;
            std::string currVar = 'x'+std::to_string(j+1);
            var.name=currVar;

            if (str[j]=='0') var.invertion=true;
            else var.invertion=false;
            op.push_back(var);
        }
       expression->push_back(op);
    }
    return ft;
}

void ShortFormParser::checkCorrectness()
{
    if (!checkOperation(_input)) throw InvalidFunctionException ("%IncorrectShortForm");

    expression->clear();
    variables.clear();
    removeUnused();

    checkBrackets();
    checkDigitsAndCommas();
    removeDoubleCommas();
}

void ShortFormParser::checkBrackets()
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

void ShortFormParser::checkDigitsAndCommas()
{
    size_t len=_input.length();

    for (size_t i=firstDigitPos;i<len-1;i++)
        if (!isdigit(_input[i]) && getSymbolType(_input[i])!=SYMBOL_COMMA)
            throw InvalidFunctionException ("%IncorrectShortForm");

    if (getSymbolType(_input[firstDigitPos])==SYMBOL_COMMA || getSymbolType(_input[len-2])==SYMBOL_COMMA)
        throw InvalidFunctionException ("%IncorrectShortForm");
}

void ShortFormParser::removeDoubleCommas()
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

void ShortFormParser::parseNumbers(std::vector<int> &numbers)
{
    std::stringstream stream (_input);
    std::string curr;

    while (std::getline(stream, curr, ','))
    {
        numbers.push_back(atoi(curr.c_str()));
    }
}

unsigned int ShortFormParser::calculateVariablesCount(const std::vector<int> &numbers)
{
    int max=0;
    size_t len = numbers.size();
    for (size_t i=0;i<len;i++)
        if (numbers[i]>max) max=numbers[i];
    if (max==0) return 1;

    double logmax = log2(max);

    return floor(logmax)+1;
}

std::string ShortFormParser::numberToBinary(int number, int size)
{
    std::string str;
    for (int j = 0; j < size; j++)
            str = ((number & (1 << j))? "1" : "0") + str;
    return str;
}
