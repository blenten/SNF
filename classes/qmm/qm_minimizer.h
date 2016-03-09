#ifndef KM_MINIMIZER_H
#define KM_MINIMIZER_H

#include "../snf_parser/snf_parserfacade.h"

class QM_Minimizer
{
public:
    QM_Minimizer();
    ~QM_Minimizer();

    inline QMExp getExp(){ return exp; }

    void match(QMExp match_exp);
protected:
    virtual SNF_ParserFacade* createParser();
    QMOperand* matchOps(QMOperand &op1, QMOperand &op2, int &match_index);
    void toGroups(QMExp &expression, Groups &res);
    void firstMatch(QMExp &match_exp, Groups &res);
    void secMatch(QMExp &match_exp, Groups &match_groups);
    int opsize;
private:
    SNF_ParserFacade *parser;
    FunctionType expType;
    QMExp exp;
};

#endif // KM_MINIMIZER_H
