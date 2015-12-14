/**
  \file
  */
#ifndef SHORTFORMPARSER_H
#define SHORTFORMPARSER_H

#include "parser.h"
#include <vector>
#include <sstream>

/**
 * @brief ShortFormParser
 *
 * Персер для сокращенной (числовой) формы ввода
 */
class ShortFormParser: public Parser
{
private:
    const size_t firstDigitPos = 2; ///<позиция с первым числом

    std::vector<int> numbers; ///< список считанных чисел

    /**
     * @brief checkCorrectness
     *
     * Проверяет корректность введенной функции
     * @throw InvalidFunctionException
     */
    void checkCorrectness();
    /**
     * @brief removeUseless
     *
     * Убирает неиспользуемые при записи функций символы из строки
     */
    void removeUseless();
    /**
     * @brief checkBrackets
     *
     * Проверяет правильность взаимного расположения скобок
     * @throw InvalidFunctionException
     */
    void checkBrackets();
    /**
     * @brief checkDigitsAndCommas
     *
     * Проверяет правильность расстановки чисел и запятых
     *
     * @throw InvalidFunctionException
     */
    void checkDigitsAndCommas();

    /**
     * @brief removeDoubleCommas
     *
     * Убирает двойные запятые, оставляя одну
     */
    void removeDoubleCommas();

    /**
     * @brief parseNumbers
     *
     * Считывает числа из строки
     */
    void parseNumbers();

    /**
     * @brief calculateVariablesCount
     *
     * Считает минимальное число переменных, которые необходимо использовать для записи функции по формуле \f$floor(\log_2(max)+1)))\f$
     * @return Число
     */
    int calculateVariablesCount();

    /**
     * @brief fillExpression
     *
     * Переводит числа в развернутую форму и заполняет выражение
     */
    void fillExpression();

    /**
     * @brief numberToBinary
     *
     * Переводит число в двоичную форму в виде строки
     * @param number - число
     * @param size - количество разрядов
     * @return Строка с числом
     */
    std::string numberToBinary(int number, int size);

public:
    /**
     * @brief parse
     *
     * Производная функции базового класса
     * @param input - входная строка
     * @param output - выходное выражение для последующей обработки
     * @return СНДФ или СНКФ
     */
    FunctionType parse (std::string input, Expression &output);
};

#endif // SHORTFORMPARSER_H
