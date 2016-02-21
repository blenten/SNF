#ifndef QM_OPERAND_H
#define QM_OPERAND_H

#include <QString>

class QMOperand
{
public:
    QMOperand();
    QMOperand(QString str);
    QString vars;
    bool matched;
};

typedef std::vector<QMOperand> QMExp;

#endif // QM_OPERAND_H
