/**
  \file
  */

#ifndef SNF_PARSERDECORATOR_H
#define SNF_PARSERDECORATOR_H
#include "shortformparser.h"
#include "expandedformparser.h"

/**
 * @brief SNF_ParserFacade
 *
 * Реализует паттерн "Фасад" для выбора нужного парсера
 */
class SNF_ParserFacade
{
private:

 /**
 * @brief getFunctionInputForm
 *
 * Определяет форму, в которой была введена функция
 * @param input - введенная функция
 * @return
 */
FunctionInputForm getFunctionInputForm (std::string input);

public:
/**
     * @brief parse
     *
     * Осуществляет парсинг функции одним из производных классов парсера
     * @param input
     * @param output
     * @return
     */
    FunctionType parse  (std::string input, Expression &output);
};

#endif // SNF_PARSERDECORATOR_H
