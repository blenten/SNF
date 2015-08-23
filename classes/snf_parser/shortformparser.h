#ifndef SHORTFORMPARSER_H
#define SHORTFORMPARSER_H

#include "parser.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <math.h>

class ShortFormParser: public Parser
{
private:
    std::string numberToBinary(int number, int size);

    const size_t firstDigitPos=2;

    std::vector<int> numbers;

    void checkCorrectness();
    void removeUnused();
    bool hasOperationSymbolAtBeginning(const std::string & input); //MOVE TO PARSER CHANGER
    void checkBrackets();
    void checkDigitsAndCommas();
    void removeDoubleCommas();

    void parseNumbers(std::vector<int> &numbers);
    unsigned int calculateVariablesCount (const std::vector<int> &numbers);

    void fillExpression();

public:
    FunctionType parse (std::string input, Expression &output);
};

#endif // SHORTFORMPARSER_H
