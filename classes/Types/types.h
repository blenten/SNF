#ifndef TYPES_H
#define TYPES_H

#include "ctype.h"

enum FunctionType {
    OTHER=-1, SNDF, SNKF
};

enum SymbolType
{
    SYMBOL_CONJUNCTION,
    SYMBOL_DISJUNCTION,
    SYMBOL_LBRACKET,
    SYMBOL_RBRACKET,
    SYMBOL_INVERSE,
    SYMBOL_OPERAND,
    SYMBOL_ZERO,
    SYMBOL_SPACE,
    SYMBOL_COMMA,
    SYMBOL_OTHER
};

SymbolType getSymbolType(char symb);


#endif //TYPES_H
