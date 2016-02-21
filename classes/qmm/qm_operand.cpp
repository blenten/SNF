#include "qm_operand.h"

QMOperand::QMOperand()
{
    matched = false;
    vars.clear();
}

QMOperand::QMOperand(QString str)
{
    matched = false;
    vars = str;
}
