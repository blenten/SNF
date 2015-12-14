/**
  \file
  */

#ifndef OPERAND_H
#define OPERAND_H

#include "lvar.h"

/**
 * @brief Operand
 *
 * Операнд функции
 */
class Operand
{
public:
    std::vector<Variable> variables; ///< список содержащихся переменных

    /**
     * @brief operator ==
     *
     * Перегруженный оператор сравнения
     * @param op
     * @return
     */
    bool operator==(Operand& op);
};

typedef vector<Operand> Expression;

#endif // OPERAND_H
