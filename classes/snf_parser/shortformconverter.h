#ifndef SHORTFORMCONVERTER_H
#define SHORTFORMCONVERTER_H

#include "../Exceptions/invalidfunctionexception.h"
#include "../Types/types.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <math.h>

//converts functions in short form (e.g. &(1,3,4,7)) into their expanded form
class ShortFormConverter
{
private:
    static void checkCorrectness();
    static void checkBrackets();
    static void checkDigitsAndCommas();
    static void removeDoubleCommas();

    static void parseNumbers(std::vector<int> &numbers);
    static unsigned int calculateVariablesCount (const std::vector<int> &numbers);

    static std::string numberToBinary(int number, int size);

    static const size_t firstDigitPos=2;

    static std::string _input;

public:
    static bool checkOperation(const std::string & input);
    static std::string convertToExpandedForm(std::string input);
};

#endif // SHORTFORMCONVERTER_H
