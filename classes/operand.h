#ifndef OPERAND_H
#define OPERAND_H

#include "lvar.h"

class Operand
{
public:
    std::vector<Variable> variables;
    bool operator == (Operand& op);
};

typedef vector<Operand> Expression;

#endif // OPERAND_H
