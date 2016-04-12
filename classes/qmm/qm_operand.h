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
    bool operator==(const QMOperand &op) const;
};

typedef std::vector<QMOperand> QMExp;
typedef std::vector<QMExp> Groups;

#endif // QM_OPERAND_H
