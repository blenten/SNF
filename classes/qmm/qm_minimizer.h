#ifndef KM_MINIMIZER_H
#define KM_MINIMIZER_H

#include "../snf_parser/snf_parserfacade.h"

class QM_Minimizer
{
public:
    QM_Minimizer();
    ~QM_Minimizer();

protected:
    SNF_ParserFacade* createParser();
    QMOperand* matchOps(QMOperand &op1, QMOperand &op2);

    SNF_ParserFacade *parser;
    FunctionType expType;
    QMExp exp;
};

#endif // KM_MINIMIZER_H
