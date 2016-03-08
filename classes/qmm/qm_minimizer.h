#ifndef KM_MINIMIZER_H
#define KM_MINIMIZER_H

#include "../snf_parser/snf_parserfacade.h"

class QM_Minimizer
{
public:
    QM_Minimizer();
    ~QM_Minimizer();

    inline QMExp getExp(){ return exp; }
protected:
    SNF_ParserFacade* createParser();
    QMOperand* matchOps(QMOperand &op1, QMOperand &op2, int &match_index);
    void toGroups(QMExp &expression, Groups &res);
    void firstMatch(QMExp &match_exp, Groups &res);
private:
    int opsyze;
    SNF_ParserFacade *parser;
    FunctionType expType;
    QMExp exp;
};

#endif // KM_MINIMIZER_H
