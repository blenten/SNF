#ifndef KM_MINIMIZER_H
#define KM_MINIMIZER_H

#include <tuple>
#include <QObject>

#include "../snf_parser/snf_parserfacade.h"
#include "qm_operand.h"

class QM_Minimizer: public QObject
{
      Q_OBJECT

public:
    QM_Minimizer();
     ~QM_Minimizer();

    inline QMExp get_currexp(){ return curr_exp; }

    QString expToQStr(QMExp &exp);

    QMExp match(QMExp &match_exp);
    QString minimize(QString input);
    QMExp getOptimalCover(QMExp &matched_ops, QMExp &input_ops);

protected:
    virtual SNF_ParserFacade* createParser();

    void set_opsize(int new_size);
    void set_currexp(QMExp exp);

    void delsame(Groups &temp);
    bool inExp(QMOperand &op, QMExp &exp);

    pair<QMOperand*, int> matchOps(QMOperand &op1, QMOperand &op2);
    void toGroups(QMExp &expression, Groups &res);
    void export_unmatched(Groups &temp, QMExp &res_exp);
    void firstMatch(QMExp &match_exp, Groups &match_groups);
    void secMatch(QMExp &match_exp, Groups &match_groups);

    void sort_implicants(QMExp &matched_ops, vector<int> &rating, int first, int last);
    void del_dupl_implicants(QMExp &matched_ops, QMExp &input_ops);
    bool covers(QMOperand &matched_op, QMOperand &input_op);
    QMExp get_covered(QMOperand &matched_op, QMExp &input_ops);
    void del_covered(QMOperand &match_op, QMExp &input_ops);
    QMExp cutCore(QMExp &matched_ops, QMExp &input_ops);

private:
    SNF_ParserFacade *parser;
    int opsize;
    FunctionType curr_exp_Type;
    QMExp curr_exp;

signals:
    void sendCondition(QString condition);
    void sendLog(QString log);
    void sendSleep (int ms);
    void sendProgress (int val);
};

#endif // KM_MINIMIZER_H
