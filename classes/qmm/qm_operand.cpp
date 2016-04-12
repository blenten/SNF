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

bool QMOperand::operator==(const QMOperand &op) const
{
    if(vars.size()!=op.vars.size()) return false;
    for(int i=0; i<(int)vars.size(); i++)
    {
        if(vars[i]!=op.vars[i])
        {
            return false;
        }
    }
    return true;
}
