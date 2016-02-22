#ifndef SHORTFORMPARSER_H
#define SHORTFORMPARSER_H

#include "parser.h"
#include <vector>
#include <sstream>

class ShortFormParser: public Parser
{
private:
    const size_t firstDigitPos = 2;

    std::vector<int> numbers;

    void checkCorrectness();

    void removeUseless();

    void checkBrackets();

    void checkDigitsAndCommas();

    void removeDoubleCommas();

    void parseNumbers();

    int calculateVariablesCount();

    void fillExpression();

    std::string numberToBinary(int number, int size);

public:
    FunctionType parse (std::string input, Expression &output);
};

#endif // SHORTFORMPARSER_H
