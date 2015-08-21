#ifndef SHORTFORMPARSER_H
#define SHORTFORMPARSER_H

#include "snf_parser.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <math.h>

class ShortFormParser: public SNF_Parser
{
private:
    std::string numberToBinary(int number, int size);

    const size_t firstDigitPos=2;

    void checkCorrectness();
    void checkBrackets();
    void checkDigitsAndCommas();
    void removeDoubleCommas();

    void parseNumbers(std::vector<int> &numbers);
    unsigned int calculateVariablesCount (const std::vector<int> &numbers);

public:
    FunctionType parse (std::string input, Expression &output);
};

#endif // SHORTFORMPARSER_H
