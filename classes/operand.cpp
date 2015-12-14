/**
  \file
  */

#include "operand.h"

bool Operand::operator==(Operand& op)
{
    if(variables.size() != op.variables.size()) return false;

    for(size_t i=0; i<variables.size(); i++)
    {
        if(!(variables[i] == op.variables[i]))
            return false;
    }
    return true;
}
