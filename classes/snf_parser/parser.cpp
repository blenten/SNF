#include "parser.h"
#include <iostream>

Parser::~Parser(){}

QMExp Parser::expressionToQMExp(Expression &input)
{
    QMExp exp;

    size_t operandsNumber = input.size();
    size_t variablesNumber = input[0].variables.size();

    for (size_t i=0;i<operandsNumber;i++)
    {
        QMOperand operand;
        operand.vars="";

        for(size_t j = 0;j<variablesNumber;j++)
            operand.vars+=(input[i].variables[j].inversion)?"0" :"1";

        exp.push_back(operand);
    }
    return exp;
}
