/**
  \file
  */

#ifndef TYPES_H
#define TYPES_H

#include "ctype.h"
#include <string>

/**
 * @brief FunctionType
 *
 * Перечисление типов функции
 */
enum FunctionType
{
    OTHER=-1,
    SNDF,
    SNKF
};

/**
 * @brief FunctionInputForm
 *
 * Перечисление форм ввода функций
 */
enum FunctionInputForm
{
    FORM_EXPANDED,
    FORM_SHORT
};

/**
 * @brief SymbolType
 *
 * Перечисление типов символа
 */
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

/**
 * @brief getSymbolType
 *
 * Определяет тип символа
 * @param symb - символ
 * @return Тип
 */
SymbolType  getSymbolType(char symb);



#endif //TYPES_H
