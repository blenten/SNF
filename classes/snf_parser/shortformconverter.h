#ifndef SHORTFORMCONVERTER_H
#define SHORTFORMCONVERTER_H

#include "../Exceptions/invalidfunctionexception.h"
#include "../Types/types.h"

//converts functions in short form (e.g. &(1,3,4,7)) into their expanded form
class ShortFormConverter
{
private:
    static bool isFunctionInCorrectShortForm();
    static void checkBrackets();
    static void checkDigitsAndCommas();
    static void removeDoubleCommas();

    static const size_t firstDigitPos=2;

    static std::string _input;

public:
    static std::string tryConvertToExpandedForm(std::string input);
};

#endif // SHORTFORMCONVERTER_H
